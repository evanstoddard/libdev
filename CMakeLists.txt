cmake_minimum_required(VERSION 3.22)

find_package(Python3 REQUIRED COMPONENTS Interpreter)

add_library(libdev INTERFACE)
target_include_directories(libdev INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# libdev_add_to_target(<target> DEF_FILE <path/to/device.def>)
#
# Wires a target up to libdev: adds libdev's include path, generates
# device_instances.inc from the given device.def, and makes sure that
# generation happens before the target is built.
function(libdev_add_to_target target)
    cmake_parse_arguments(ARG "" "DEF_FILE" "" ${ARGN})
    if(NOT ARG_DEF_FILE)
        message(FATAL_ERROR "libdev_add_to_target: DEF_FILE argument required")
    endif()

    get_filename_component(DEF_FILE_ABS ${ARG_DEF_FILE} ABSOLUTE)
    get_filename_component(DEF_FILE_DIR ${DEF_FILE_ABS} DIRECTORY)
    get_filename_component(DEF_FILE_NAME "${DEF_FILE_ABS}" NAME)


    # Namespaced per-target so multiple targets can each pass their own
    # device.def without their generated outputs colliding.
    set(GEN_DIR ${CMAKE_BINARY_DIR}/libdev/generated/${target})
    set(DEVICE_INSTANCES_INC ${GEN_DIR}/device_instances.inc)

    # CMAKE_CURRENT_FUNCTION_LIST_DIR resolves to the directory this
    # function was *defined* in (libdev's own root), regardless of which
    # directory scope the function is *called* from. Plain
    # CMAKE_CURRENT_SOURCE_DIR wouldn't work here: it would resolve to
    # whatever directory is calling this function, not libdev's own.
    add_custom_command(
        OUTPUT ${DEVICE_INSTANCES_INC}
        COMMAND ${CMAKE_COMMAND} -E make_directory ${GEN_DIR}
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/scripts/gen_device_instances.py
                ${DEF_FILE_ABS} ${DEVICE_INSTANCES_INC}
        DEPENDS ${DEF_FILE_ABS} ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/scripts/gen_device_instances.py
        COMMENT "libdev: generating device_instances.inc for ${target}"
        VERBATIM
    )
    add_custom_target(${target}_libdev_generate DEPENDS ${DEVICE_INSTANCES_INC})
    add_dependencies(${target} ${target}_libdev_generate)

    target_link_libraries(${target} libdev)
    target_include_directories(${target} PRIVATE ${GEN_DIR} ${DEF_FILE_DIR})
    target_compile_definitions(${target} PRIVATE LIBDEV_DEFINITION_INCLUDE="${DEF_FILE_NAME}")

endfunction()
