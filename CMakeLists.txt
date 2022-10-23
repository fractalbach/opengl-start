cmake_minimum_required(VERSION 2.8.12)
project(opengl-start)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()


# Converting the shader source code into strings that we can directly access
SET(RESOURCE_COMPILER xxd)
FILE(GLOB_RECURSE COMPILED_RESOURCES "shaders/*")
FOREACH(INPUT_FILE ${COMPILED_RESOURCES})
    get_filename_component(INPUT_FILE ${INPUT_FILE} NAME)
    SET(OUTPUT_FILE build/shaders/${INPUT_FILE}.hex)
    SET(INPUT_FILE shaders/${INPUT_FILE})
    ADD_CUSTOM_COMMAND(
        OUTPUT ${OUTPUT_FILE}
        WORKING_DIRECTORY ../ 
        COMMAND ${CMAKE_COMMAND} -E make_directory "build/shaders"
        COMMAND ${RESOURCE_COMPILER} -i ${INPUT_FILE} ${OUTPUT_FILE}
        COMMENT "Compiling ${INPUT_FILE} to binary")
    LIST(APPEND COMPILED_RESOURCES ${OUTPUT_FILE})
ENDFOREACH()


add_executable(main main.cpp ${COMPILED_RESOURCES})
target_link_libraries(main ${CONAN_LIBS})
