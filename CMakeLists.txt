cmake_minimum_required(VERSION 3.16)
project(fleaux LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include(cmake/utilities.cmake)

enable_warnings()

option(COVERAGE "Enable code coverage flags")
option(SANITIZE "Enable sanitizer flags")
option(FLEAUX_USE_FETCH_CONTENT "Use FetchContent to get dependencies" ON)

if (COVERAGE)
    enable_coverage()
endif ()

if (SANITIZE)
    enable_sanitizer()
endif ()

if(FLEAUX_USE_FETCH_CONTENT)
    include(FetchContent)
endif()

if(${FLEAUX_USE_FETCH_CONTENT})
    FetchContent_Declare(
            data_tree
            GIT_REPOSITORY "https://github.com/mguid65/datatree"
            GIT_TAG "v0.0.5"
    )
    FetchContent_MakeAvailable(data_tree)
else()
    find_package(data_tree REQUIRED)
endif()

find_package(tl-expected REQUIRED)

set(FLEAUX_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/include/fleaux/fleaux.hpp
)

set(FLEAUX_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/source/fleaux/fleaux.cpp
)

set(DATA_TREE_INCLUDE_DIR ${data_tree_SOURCE_DIR}/include)

add_library(fleaux STATIC)
target_include_directories(fleaux PUBLIC include)
target_sources(fleaux PRIVATE ${FLEAUX_SOURCES} ${FLEAUX_HEADERS})
target_link_libraries(fleaux PUBLIC data_tree)
set_target_properties(fleaux PROPERTIES LINKER_LANGUAGE CXX)

#include(CTest)

install(DIRECTORY include/ DESTINATION include)
install(TARGETS fleaux DESTINATION lib)

add_executable(main)
target_sources(main PRIVATE source/sample/main.cpp)
target_link_libraries(main PRIVATE fleaux)

#enable_testing()
#
#add_test(NAME sample
#        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
#        COMMAND sample)

#find_package(Catch2 COMPONENTS Catch2WithMain)
#
#if (Catch2_FOUND)
#    add_subdirectory(test)
#endif ()