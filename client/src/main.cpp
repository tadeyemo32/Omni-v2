#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h> // Will include OpenGL headers

int main() {
    // Init GLFW
    if (!glfwInit()) return -1;
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Finance App", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // Init ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 150");

    // Example finance state
    float income = 5000.0f;
    float expenses = 3200.0f;

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Finance Dashboard Window
        ImGui::Begin("Finance Dashboard");

        ImGui::Text("Monthly Income: %.2f", income);
        ImGui::Text("Monthly Expenses: %.2f", expenses);

        float balance = income - expenses;
        ImGui::Text("Balance: %.2f", balance);

        ImGui::SliderFloat("Adjust Income", &income, 0.0f, 10000.0f);
        ImGui::SliderFloat("Adjust Expenses", &expenses, 0.0f, 10000.0f);

        ImGui::End();

        // Render
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
