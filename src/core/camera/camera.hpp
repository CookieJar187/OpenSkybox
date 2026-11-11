#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct Camera{

private:
    GLFWwindow* window;

    float yaw = 0.0f;
    float pitch = 0.0f;

    double previousMouseX = 0.0;
    double previousMouseY = 0.0;

    bool wasRotating = false;

    const float sensitivity = 0.15f;

public:
    Camera(GLFWwindow* window) : window(window) {}
    void update();
    void apply(unsigned int shaderProgram);
};