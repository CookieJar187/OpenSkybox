cmake_minimum_required(VERSION 3.20)

project(program LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(Stb REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

add_executable(program
    src/main.cpp
    src/core/camera/camera.cpp
    src/core/loaders/shader_loader/shader_loader.cpp
    src/core/loaders/texture_loader/texture_loader.cpp

    # UI
    src/ui/ui_root.cpp
    src/ui/screens/main_menu_screen.cpp
    src/ui/screens/editor_screen.cpp
    src/ui/screens/editor_elements/file_menu_bar_ui.cpp
    src/ui/screens/editor_elements/properties_ui.cpp
    src/ui/screens/editor_elements/properties_ui_elements/atmosphere_ui.cpp
    src/ui/screens/editor_elements/properties_ui_elements/sun_ui.cpp
    src/ui/screens/editor_elements/properties_ui_elements/clouds_ui.cpp
)

target_include_directories(program PRIVATE
    src/core/camera
    src/core/state
    src/core/properties
    src/core/loaders/shader_loader
    src/core/loaders/texture_loader
    src/core/texture

    # UI
    src/ui
    src/ui/screens
    src/ui/screens/editor_elements

    ${Stb_INCLUDE_DIR}
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