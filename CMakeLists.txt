cmake_minimum_required(VERSION 3.20)

project(program LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

add_executable(program
    src/main.cpp
    src/core/shader_loader/shader_loader.cpp
    src/core/camera/camera.cpp

    # UI
    src/ui/ui_root.cpp
    src/ui/screens/main_menu_screen.cpp
    src/ui/screens/editor_screen.cpp
)

target_include_directories(program PRIVATE
    src/core/shader_loader
    src/core/camera
    src/core/state
    src/core/properties

    # UI
    src/ui
    src/ui/screens
)

target_link_libraries(program PRIVATE
    glfw
    glad::glad
    imgui::imgui
)

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(program PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -Werror=return-type
    )
endif()