//
// Created by niek on 2025/07/09.
//

#include "core/Polykernel_Impl.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdexcept>

namespace polykami::core {

    polykernel::Impl::Impl() : initialized(false) { }
    polykernel::Impl::~Impl() = default;

    void polykernel::Impl::initializeOpenGL() {
        if (!glfwInit()) {
            throw std::runtime_error("Failed to initialize GLFW");
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        initialized = true;
    }

    void polykernel::Impl::loadGLAD() {
        if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
            throw std::runtime_error("Failed to initialize GLAD");
        }
    }

    void polykernel::Impl::cleanup() {
        if (initialized) {
            glfwTerminate();
            initialized = false;
        }
    }

    void polykernel::Impl::setViewport(const int width, const int height) const {
        if (initialized) {
            glViewport(0, 0, width, height);
        }
    }

    void polykernel::Impl::clearFrame(const float r, const float g, const float b, const float a) const {
        if (initialized) {
            glClearColor(r, g, b, a);
            glClear(GL_COLOR_BUFFER_BIT);
        }
    }

}  // polykami::core