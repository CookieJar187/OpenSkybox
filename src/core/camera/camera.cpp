#include <algorithm>

#include "camera.hpp"

void Camera::update()
{
    bool rotating = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS;

    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);

    if (rotating)
    {
        if (wasRotating)
        {
            float deltaX = static_cast<float>(mouseX - previousMouseX);
            float deltaY = static_cast<float>(mouseY - previousMouseY);

            yaw += deltaX * sensitivity;
            pitch -= deltaY * sensitivity;

            pitch = std::clamp(pitch, -89.0f, 89.0f);
        }

        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    else
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    previousMouseX = mouseX;
    previousMouseY = mouseY;
    wasRotating = rotating;
}

void Camera::apply(unsigned int shaderProgram)
{
    glUniform2f(
        glGetUniformLocation(shaderProgram, "uCameraAngles"),
        yaw,
        pitch
    );
}