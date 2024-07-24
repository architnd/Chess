#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

// Global variables for square position
float squareX = 100.0f;
float squareY = 100.0f;
const float squareSize = 50.0f;
const float moveSpeed = 10.0f;

// Function to initialize GLFW and OpenGL
bool InitGLFWAndOpenGL(GLFWwindow*& window, const char* windowTitle) {
    if (!glfwInit()) {
        return false;
    }

    // Get the primary monitor and its video mode
    GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(primaryMonitor);

    // Set GLFW to use OpenGL 3.3 with core profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a full-screen window
    window = glfwCreateWindow(mode->width, mode->height, windowTitle, primaryMonitor, nullptr);
    if (window == nullptr) {
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    return true;
}

// Function to initialize ImGui
void InitImGui(GLFWwindow* window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

// Function to clean up and terminate
void Cleanup(GLFWwindow* window) {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
}

// Function to handle keyboard input for moving the square
void HandleKeyboardInput(GLFWwindow* window) {
    int windowWidth, windowHeight;
    glfwGetWindowSize(window, &windowWidth, &windowHeight);

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        if (squareY - moveSpeed >= 0) {
            squareY -= moveSpeed;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        if (squareY + squareSize + moveSpeed <= windowHeight) {
            squareY += moveSpeed;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        if (squareX - moveSpeed >= 0) {
            squareX -= moveSpeed;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        if (squareX + squareSize + moveSpeed <= windowWidth) {
            squareX += moveSpeed;
        }
    }
}

int main(int, char**) {
    GLFWwindow* window;

    // Initialize GLFW and OpenGL
    if (!InitGLFWAndOpenGL(window, "ImGui Example")) {
        return -1;
    }

    // Initialize ImGui
    InitImGui(window);

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        // Poll and handle events
        glfwPollEvents();
        
        // Handle keyboard input
        HandleKeyboardInput(window);

        // Start the ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Draw a blue square
        ImDrawList* draw_list = ImGui::GetForegroundDrawList();
        ImVec2 p = ImVec2(squareX, squareY); // Position of the square
        ImU32 col = ImColor(0, 0, 255); // Blue color
        draw_list->AddRectFilled(p, ImVec2(p.x + squareSize, p.y + squareSize), col);

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // Cleanup
    Cleanup(window);

    return 0;
}
