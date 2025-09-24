cmake_minimum_required(VERSION 3.16)
project(render-sfml VERSION 1.0.0 DESCRIPTION "Render subsystem using SFML")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG        3.0.2
)
FetchContent_MakeAvailable(SFML)

find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)

file(GLOB_RECURSE SRC CONFIGURE_DEPENDS src/*.cpp)

add_library(${PROJECT_NAME} SHARED ${SRC})

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../common/include
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        SFML::Graphics
        SFML::Window
        SFML::System
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_NAME render_sfml
    SUFFIX ".so"
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib
)

install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/include")
    install(DIRECTORY include/ DESTINATION include)
endif()
