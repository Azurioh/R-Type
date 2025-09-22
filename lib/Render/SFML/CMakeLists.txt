cmake_minimum_required(VERSION 3.10)
project(render-sfml VERSION 1.0.0 DESCRIPTION "The render subsytem using SFML")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 3 COMPONENTS Graphics Window System QUIET)

include(GNUInstallDirs)

SET(INCLUDE_COMMON_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../common/include")

if(NOT SRC)
    message(FATAL_ERROR "Aucun fichier source trouvé dans src/")
endif()

if(NOT SFML_FOUND)
    message(STATUS "SFML not found via find_package, using pkg-config...")
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(SFML REQUIRED sfml-graphics sfml-window sfml-system)
endif()

file(GLOB_RECURSE SRC CONFIGURE_DEPENDS src/*.cpp)

add_library(${PROJECT_NAME} SHARED ${SRC})

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${INCLUDE_COMMON_PATH}
)

if(TARGET SFML::Graphics)
    message(STATUS "Using SFML 3.x targets")
    target_link_libraries(${PROJECT_NAME}
        PRIVATE
            SFML::Graphics
            SFML::Window
            SFML::System
    )
else()
    message(STATUS "Using pkg-config for SFML")
    target_include_directories(${PROJECT_NAME} PRIVATE ${SFML_INCLUDE_DIRS})
    target_compile_options(${PROJECT_NAME} PRIVATE ${SFML_CFLAGS_OTHER})

    foreach(lib ${SFML_LIBRARIES})
        find_library(${lib}_PATH ${lib} HINTS ${SFML_LIBRARY_DIRS})
        if(${lib}_PATH)
            target_link_libraries(${PROJECT_NAME} PRIVATE ${${lib}_PATH})
        else()
            target_link_libraries(${PROJECT_NAME} PRIVATE ${lib})
        endif()
    endforeach()

    target_link_directories(${PROJECT_NAME} PRIVATE ${SFML_LIBRARY_DIRS})
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_NAME render_sfml
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

if(APPLE)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        SUFFIX ".so"
        MACOSX_RPATH OFF
    )
endif()

install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/include")
    install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
endif()
