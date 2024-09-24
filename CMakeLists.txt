cmake_minimum_required(VERSION 3.19)
project(PythonCppHomogeneousContainers)

function(dump_cmake_variables)
    message(STATUS "==== dump_cmake_variables()")
    get_cmake_property(_variableNames VARIABLES)
    list (SORT _variableNames)
    foreach (_variableName ${_variableNames})
        if (ARGV0)
            unset(MATCHED)
            string(REGEX MATCH ${ARGV0} MATCHED ${_variableName})
            if (NOT MATCHED)
                continue()
            endif()
        endif()
        message(STATUS "${_variableName}=${${_variableName}}")
    endforeach()
    message(STATUS "==== dump_cmake_variables() DONE")
endfunction()

set(CMAKE_CXX_STANDARD 14)

# To deal with:
# ld: warning: ignoring file /usr/local/Frameworks/Python.framework/Versions/3.11/lib/libpython3.11.dylib, building for macOS-arm64 but attempting to link with file built for macOS-x86_64
set(CMAKE_OSX_ARCHITECTURES "x86_64")

add_compile_options(
        "-Wall"
        "-Wextra"
        "-Wpedantic"
        "-Werror"
        "-Wfatal-errors"
        "-Wno-unused-variable" # Temporary
        "-Wno-unused-parameter" # Temporary
        "-fexceptions"
        # To allow designated initialisers.
        "-Wno-c99-extensions"
#        "-Wc99-extensions"
        "$<$<CONFIG:DEBUG>:-O0;-g3;-ggdb>"
)


#link_directories(
#        /Library/Frameworks/Python.framework/Versions/3.8/lib
#)

include_directories(
        src
)

#SET(Python3_DIR "/Library/Frameworks/Python.framework/Versions/3.9")

FIND_PACKAGE (Python3 3.12 EXACT REQUIRED COMPONENTS Interpreter Development)# PATH_SUFFIXES "/Library/Frameworks/Python.framework/Versions")
#FIND_PACKAGE(PythonLibs 3.11 EXACT REQUIRED)
#SET(PythonLibs_DIR "/Library/Frameworks/Python.framework/Versions/3.8")
#FIND_PACKAGE(PythonLibs 3.8 REQUIRED PATHS ("/Library/Frameworks/Python.framework/Versions/3.8"))
#FindPythonLibs()
IF (Python3_FOUND)
    INCLUDE_DIRECTORIES("${Python3_INCLUDE_DIRS}")
#    message("Python3_LOBRARY:           ${PYTHON_LIBRARY}")
#    get_filename_component(PYTHON_LINK_DIRECTORY ${PYTHON_LIBRARY} DIRECTORY)
    # See: https://cmake.org/cmake/help/latest/module/FindPython3.html#module:FindPython3
    message("Python3_VERSION:           ${Python3_VERSION}")
    message("Python3_EXECUTABLE:        ${Python3_EXECUTABLE}")
    message("Python3_INTERPRETER_ID:    ${Python3_INTERPRETER_ID}")
    message("Python3_INCLUDE_DIRS:      ${Python3_INCLUDE_DIRS}")
    message("Python3_STDLIB:            ${Python3_STDLIB}")
    message("Python3_STDARCH:           ${Python3_STDARCH}")
    message("Python3_LINK_OPTIONS:      ${Python3_LINK_OPTIONS}")
    message("Python3_LIBRARIES:         ${Python3_LIBRARIES}")
ELSE ()
    MESSAGE(FATAL_ERROR "Unable to find Python libraries.")
ENDIF ()


#FIND_PACKAGE(PythonLibs 3.9 REQUIRED)
#IF(PYTHONLIBS_FOUND)
#    message(status "    Python libraries: ${PYTHON_LIBRARIES}")
#    message(status " Python include dirs: ${PYTHON_INCLUDE_DIRS}")
#    message(status "      Python version: ${PYTHONLIBS_VERSION_STRING}")
#    message(status "      Python library: ${PYTHON_LIBRARY}")
#    message(status "  Python include dir: ${PYTHON_INCLUDE_DIR}")
#    INCLUDE_DIRECTORIES("${PYTHON_INCLUDE_DIRS}")
#ELSE()
#    MESSAGE(FATAL_ERROR "Unable to find Python libraries.")
#ENDIF()

add_executable(
        PythonCppHomogeneousContainers
        src/main.cpp

        src/cpp/get_rss.cpp
        src/cpp/get_rss.h
        src/cpp/TestFramework.cpp
        src/cpp/TestFramework.h
        src/cpp/save_stream_state.h

        src/cpy/auto_py_convert_internal.h
        src/cpy/auto_py_convert_internal.cpp
        src/cpy/python_convert.h
        src/cpy/python_object_convert.h
        src/cpy/python_object_convert.cpp
        src/cpy/python_container_convert.h
        src/cpy/python_container_convert.cpp

        src/cpy/tests/test_functional.cpp
        src/cpy/tests/test_functional.h
        src/cpy/tests/test_performance.cpp
        src/cpy/tests/test_performance.h
        src/cpy/tests/test_common.h
        src/cpy/tests/test_common.cpp
        src/cpy/tests/test_memory.cpp
        src/cpy/tests/test_memory.h

        src/ext/cPyCppContainers.cpp
        src/ext/cUserDefined.cpp
        src/ext/cUserDefined.h)

#SET(CMAKE_BUILD_RPATH "/Applications/Xcode.app/Contents/Developer/Library/Frameworks/Python3.framework/Versions/3.9")
#MESSAGE("CMAKE_BUILD_RPATH:" ${CMAKE_BUILD_RPATH})
#MESSAGE("BUILD_RPATH:" ${BUILD_RPATH})
#
#SET(BUILD_WITH_INSTALL_RPATH TRUE)
#SET(CMAKE_INSTALL_RPATH "/Applications/Xcode.app/Contents/Developer/Library/Frameworks/Python3.framework/Versions/3.9")
#MESSAGE("CMAKE_INSTALL_RPATH:" ${CMAKE_INSTALL_RPATH})
#MESSAGE("INSTALL_RPATH:" ${INSTALL_RPATH})
#
## From: https://stackoverflow.com/questions/17703510/dyld-library-not-loaded-reason-image-not-found
#set_target_properties(${PROJECT_NAME} PROPERTIES
#        # # for FRAMEWORK begin
#        # FRAMEWORK TRUE
#        # FRAMEWORK_VERSION C
#        # MACOSX_FRAMEWORK_IDENTIFIER com.cmake.targetname
#        # MACOSX_FRAMEWORK_INFO_PLIST ./Info.plist
#        # PUBLIC_HEADER targetname.h
#        # # for FRAMEWORK end
#        IPHONEOS_DEPLOYMENT_TARGET "8.0"
#        DYLIB_INSTALL_NAME_BASE "@rpath" # this is the key point
#        XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "iPhone Developer"
#        DEVELOPMENT_TEAM "${DEVELOPMENT_TEAM}"
#)

#set(CMAKE_MACOSX_RPATH OFF)
##add_library(${Python3_LIBRARIES} SHARED)
#add_library(${PROJECT_NAME} SHARED)

#SET(Python3_INTERPRETER_ID "Python3")
#message("Python3_INTERPRETER_ID:    ${Python3_INTERPRETER_ID}")

#link_directories(${PYTHON_LINK_LIBRARY})
link_directories(${Python3_LIBRARIES})

#target_link_libraries(${PROJECT_NAME} ${PYTHON_LIBRARY})
target_link_libraries(${PROJECT_NAME} ${Python3_LIBRARIES})

MESSAGE(STATUS "Build type: " ${CMAKE_BUILD_TYPE})
MESSAGE(STATUS "Library Type: " ${LIB_TYPE})
MESSAGE(STATUS "Compiler flags:" ${CMAKE_CXX_COMPILE_FLAGS})
MESSAGE(STATUS "Compiler cxx debug flags:" ${CMAKE_CXX_FLAGS_DEBUG})
MESSAGE(STATUS "Compiler cxx release flags:" ${CMAKE_CXX_FLAGS_RELEASE})
MESSAGE(STATUS "Compiler cxx min size flags:" ${CMAKE_CXX_FLAGS_MINSIZEREL})
MESSAGE(STATUS "Compiler cxx flags:" ${CMAKE_CXX_FLAGS})

#dump_cmake_variables()
