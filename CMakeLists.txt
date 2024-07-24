cmake_minimum_required(VERSION 3.10)

project(Snake)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the executable
add_executable(Snake main.cpp)

# Include directories for ImGui
target_include_directories(Snake PRIVATE imgui imgui/backends)

# Link libraries (GLFW, OpenGL)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

target_link_libraries(Snake PRIVATE glfw OpenGL::GL)

# Link ImGui files
set(IMGUI_SRC
    imgui/imgui.cpp
    imgui/imgui_demo.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_tables.cpp
    imgui/imgui_widgets.cpp
    imgui/backends/imgui_impl_glfw.cpp
    imgui/backends/imgui_impl_opengl3.cpp
)

target_sources(Snake PRIVATE ${IMGUI_SRC})
