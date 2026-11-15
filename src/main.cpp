#include <iostream>

//#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader_loader.hpp"
#include "camera.hpp"
#include "state.hpp"
#include "ui_root.hpp"
#include "properties.hpp"

void setWindowIcon(GLFWwindow *window)
{
    int width, height, channels;

    unsigned char* pixels = stbi_load(
        "src/assets/icon.png",
        &width,
        &height,
        &channels,
        4
    );

    if (!pixels)
        throw std::runtime_error("Failed to load window icon");

    GLFWimage icon;
    icon.width = width;
    icon.height = height;
    icon.pixels = pixels;

    glfwSetWindowIcon(window, 1, &icon);

    stbi_image_free(pixels);
}

int main()
{
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW\n";
        return 1;
    }

    GLFWwindow *window = glfwCreateWindow(400, 300, "OpenSkybox", nullptr, nullptr);
    setWindowIcon(window);

    if (!window)
    {
        std::cerr << "Failed to create window\n";
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        std::cerr << "Failed to initialize GLAD\n";
        glfwDestroyWindow(window);
        glfwTerminate();
        return 1;
    }

    //
    Camera camera{window};
    State state{};
    Properties properties;

    GLuint skyVAO;
    glGenVertexArrays(1, &skyVAO);

    unsigned int skyProgram = make_shader(
        "src/shaders/sky.vert",
        "src/shaders/sky.frag");

    {
        UiRoot uiRoot{state, window, properties};

        while (!glfwWindowShouldClose(window))
        {
            glfwPollEvents();

            uiRoot.build();
            camera.update();

            int width, height;
            glfwGetFramebufferSize(window, &width, &height);

            glViewport(0, 0, width, height);

            glClear(GL_COLOR_BUFFER_BIT);

            glUseProgram(skyProgram);
            camera.apply(skyProgram);
            properties.apply(skyProgram);

            glUniform2f(
                glGetUniformLocation(skyProgram, "uResolution"),
                static_cast<float>(width),
                static_cast<float>(height)
            );

            glBindVertexArray(skyVAO);
            glDrawArrays(GL_TRIANGLES, 0, 3);

            uiRoot.draw();

            glfwSwapBuffers(window);

            if (state.getState() == StateType::Exit)
                break;
        }
    }
    
    glDeleteVertexArrays(1, &skyVAO);
    glDeleteProgram(skyProgram);
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}