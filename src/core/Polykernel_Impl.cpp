//
// Created by niek on 2025/07/09.
//

#include "core/Polykernel_Impl.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace polykami::core {
    Polykernel::Impl::Impl() : initialized(false) { }
    Polykernel::Impl::~Impl() = default;

    void Polykernel::Impl::initializeOpenGL() {
        if (!glfwInit()) {
            throw std::runtime_error("Failed to initialize GLFW");
        }

        if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
            throw std::runtime_error("Failed to initialize GLAD");
        }

        initialized = true;
    }

    void Polykernel::Impl::cleanup() {
        if (initialized) {
            glfwTerminate();
            initialized = false;
        }
    }

    void Polykernel::Impl::setViewport(const int width, const int height) const {
        if (initialized) {
            glViewport(0, 0, width, height);
        }
    }

    void Polykernel::Impl::clearFrame(const float r, const float g, const float b, const float a) const {
        if (initialized) {
            glClearColor(r, g, b, a);
            glClear(GL_COLOR_BUFFER_BIT);
        }
    }
}  // polykami::core