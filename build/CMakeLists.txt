cmake_minimum_required(VERSION 3.3)

set(ROBOT "NONE" CACHE STRING "Build BCL with the specified robot packets. By default, only core BCL messages will be built.")
set(ROBOT_CONFIG Ascent Insomnia)
set(CMAKE_BUILD_TYPE Debug)

if (${ROBOT} STREQUAL "NONE")
    project(BadgerCommandLibrary C CXX)
elseif (${ROBOT} IN_LIST ROBOT_CONFIG)
    project(${ROBOT}CommandLibrary C CXX)
else ()
    message(FATAL_ERROR "Error: ${ROBOT} is not a supported robot. Select from: ${ROBOT_CONFIG}")
endif()

if (NOT WIN32 AND NOT UNIX)
    message(FATAL_ERROR "Error: This is intended to be run from Windows or Linux. If someone wants to try implementing support for CCS, go for it!")
endif()

find_package(Threads REQUIRED)
set (CMAKE_CXX_STANDARD 11)

# BCL base dependencies
set(BCL_BASE_DIR ${CMAKE_SOURCE_DIR}/..)

include_directories(${BCL_BASE_DIR}/packet/include)
include_directories(${BCL_BASE_DIR}/services/include)

file(GLOB BCL_PACKET_SRC ${BCL_BASE_DIR}/packet/**/*)
file(GLOB BCL_SERVICES_SRC ${BCL_BASE_DIR}/services/**/*)

# Robot specific dependencies
if (${ROBOT} STREQUAL "Ascent")
    set(ASCENT_BASE_DIR ${BCL_BASE_DIR}/robot/ascent)
    include_directories(${ASCENT_BASE_DIR}/include)
    file(GLOB ASCENT_SRC ${ASCENT_BASE_DIR}/**/*)
    add_library(${PROJECT_NAME} STATIC ${ASCENT_SRC} ${BCL_PACKET_SRC} ${BCL_SERVICES_SRC})
else () 
    # default - just BCL only
    add_library(${PROJECT_NAME} STATIC ${BCL_PACKET_SRC} ${BCL_SERVICES_SRC})
endif()

target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})

# Compile options
if (MSVC)
    # Force to always compile with W4
    if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    endif()
else ()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-missing-field-initializers -pedantic -ludev")
endif()
