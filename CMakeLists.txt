cmake_minimum_required(VERSION 3.19)
project(PythonCppHomogeneousContainers)

set(CMAKE_CXX_STANDARD 14)

add_compile_options(
        "-Wall"
        "-Wextra"
        "-Wpedantic"
        "-Werror"
        "-Wfatal-errors"
        "-Wno-unused-variable" # Temporary
        "-Wno-unused-parameter" # Temporary
        "-fexceptions"
        "$<$<CONFIG:DEBUG>:-O0;-g3;-ggdb>"
)

#link_directories(
#        /Library/Frameworks/Python.framework/Versions/3.8/lib
#)

include_directories(
        src
)

FIND_PACKAGE(PythonLibs 3.9 REQUIRED)
IF(PYTHONLIBS_FOUND)
    message(status "    Python libraries: ${PYTHON_LIBRARIES}")
    message(status " Python include dirs: ${PYTHON_INCLUDE_DIRS}")
    message(status "      Python version: ${PYTHONLIBS_VERSION_STRING}")
    message(status "      Python library: ${PYTHON_LIBRARY}")
    message(status "  Python include dir: ${PYTHON_INCLUDE_DIR}")
    INCLUDE_DIRECTORIES("${PYTHON_INCLUDE_DIRS}")
ELSE()
    MESSAGE(FATAL_ERROR "Unable to find Python libraries.")
ENDIF()

add_executable(
        PythonCppHomogeneousContainers
        main.cpp
        src/auto_py_convert_internal.h
        src/auto_py_convert_internal.cpp
        src/python_convert.h
        src/python_convert.cpp
        src/TestFramework.cpp
        src/TestFramework.h
        src/save_stream_state.h
        src/test_functional.cpp
        src/test_functional.h
        src/test_performance.cpp
        src/test_performance.h
        src/test_common.h
        src/test_common.cpp)

target_link_libraries(PythonCppHomogeneousContainers ${PYTHON_LIBRARIES})


MESSAGE(STATUS "Build type: " ${CMAKE_BUILD_TYPE})
MESSAGE(STATUS "Library Type: " ${LIB_TYPE})
MESSAGE(STATUS "Compiler flags:" ${CMAKE_CXX_COMPILE_FLAGS})
MESSAGE(STATUS "Compiler cxx debug flags:" ${CMAKE_CXX_FLAGS_DEBUG})
MESSAGE(STATUS "Compiler cxx release flags:" ${CMAKE_CXX_FLAGS_RELEASE})
MESSAGE(STATUS "Compiler cxx min size flags:" ${CMAKE_CXX_FLAGS_MINSIZEREL})
MESSAGE(STATUS "Compiler cxx flags:" ${CMAKE_CXX_FLAGS})
