#include <iostream>
#include <array>

#include <imgui.h>
#include <GLFW/glfw3.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
#include <implot.h>

#include "CPU/cpu.h"
#include "memory/memory.h"

std::array<double, 120> CPUHistory = {};
std::array<double, 120> RAMHistory = {};

int historyOffsetCPU = 0;
int historyOffsetRAM = 0;

void addCPUData(double data)
{
    CPUHistory[historyOffsetCPU] = data;
    historyOffsetCPU = (historyOffsetCPU + 1) % 120;
}

void addRAMData(uint64_t usedMem, uint64_t totalMem)
{
    double usedGB = usedMem /= 1073741824.0;
    double totalGB = totalMem /= 1073741824.0;

    RAMHistory[historyOffsetRAM] = (usedGB / totalGB) * 100;
    historyOffsetRAM = (historyOffsetRAM + 1) % 120;
}

int main(int, char**){
    std::cout << "\033[?25l";

    if (!glfwInit())
    {
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(
        1280,
        720,
        "System Monitor",
        nullptr,
        nullptr
    );

    glfwMakeContextCurrent(window);

    ImGui::CreateContext();
    ImPlot::CreateContext();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);

        ImGui::Begin("System Monitor",
            nullptr,
            ImGuiWindowFlags_NoTitleBar |
            ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoScrollbar |
            ImGuiWindowFlags_NoCollapse
        );

        std::cout << "\033[H";

        double cpuUsage = getCPUUsage();
        addCPUData(cpuUsage);

        MemoryStats mem = getMemoryStats();
        addRAMData(mem.usedPhys, mem.totalPhys);
        
        ImGui::Text("CPU Usage: %.1f%%", cpuUsage);

        ImGui::Text("Total Memory: %.1f GB",
        mem.totalPhys / 1073741824.0);

        ImGui::Text("Available Memory: %.1f GB",
        mem.availPhys / 1073741824.0);
        
        ImGui::Text("Used Memory: %.1f GB",
        mem.usedPhys / 1073741824.0);

        if (ImPlot::BeginPlot("Resource Usage", ImVec2(-1, 300)))
        {
            ImPlot::SetupAxes("Time (samples)", "Usage (%)");
            ImPlot::SetupAxisLimits(ImAxis_Y1, 0.0, 100.0);

            ImPlot::PlotLine(
                "CPU",
                CPUHistory.data(),
                120
            );

            ImPlot::PlotLine(
                "RAM",
                RAMHistory.data(),
                120
            );

            ImPlot::EndPlot();
        }
 
        ImGui::End();

        ImGui::Render();

        int width, height;
        glfwGetFramebufferSize(window, &width, &height);

        glViewport(0, 0, width, height);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    std::cout << "\033[?25h";
}