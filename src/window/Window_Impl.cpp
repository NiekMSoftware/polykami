//
// Created by niek on 2025/07/08.
//

#include "window/Window_Impl.h"
#include <stdexcept>

namespace polykami::window {

    Window::Impl::Impl(const WindowProperties &properties)
        : window(nullptr), resizeCallback(nullptr), keyCallback(nullptr), mouseCallback(nullptr) {
        this->properties = properties;
    }

    Window::Impl::~Impl() = default;

    bool Window::Impl::initialize() {
        window = glfwCreateWindow(
            static_cast<int>(properties.width),
            static_cast<int>(properties.height),
            properties.title.c_str(),
            nullptr,
            nullptr
        );

        if (!window) {
            throw std::runtime_error("Failed to create GLFW window");
        }
        glfwMakeContextCurrent(window);
        glfwSetWindowUserPointer(window, this);

        // set up glfw callbacks
        glfwSetWindowSizeCallback(window, glfwResizeCallback);
        glfwSetKeyCallback(window, glfwKeyCallback);
        glfwSetMouseButtonCallback(window, glfwMouseCallback);

        return true;
    }

    void Window::Impl::update() {
        glfwPollEvents();
    }

    void Window::Impl::shutdown() const {
        glfwDestroyWindow(window);
    }

    bool Window::Impl::shouldClose() const {
        return glfwWindowShouldClose(window);
    }

    void Window::Impl::swapBuffers() const {
        glfwSwapBuffers(window);
    }

    void Window::Impl::setSize(const unsigned int width, const unsigned int height) {
        properties.width = width;
        properties.height = height;
        glfwSetWindowSize(window, static_cast<int>(properties.width), static_cast<int>(properties.height));
    }

    void Window::Impl::setTitle(const std::string &title) const {
        glfwSetWindowTitle(window, title.c_str());
    }

    void Window::Impl::setVSync(const bool enabled) {
        glfwSwapInterval(enabled ? 1 : 0);
    }

    void Window::Impl::setResizeCallback(const ResizeCallback &callback) {
        resizeCallback = callback;
    }

    void Window::Impl::setKeyCallback(const KeyCallback &callback) {
        keyCallback = callback;
    }

    void Window::Impl::setMouseCallback(const MouseCallback &callback) {
        mouseCallback = callback;
    }

    void Window::Impl::glfwResizeCallback(GLFWwindow *window, const int width, const int height) {
        // Get the Window::Impl instance from the user pointer
        if (auto* impl = static_cast<Window::Impl*>(glfwGetWindowUserPointer(window)); impl && impl->resizeCallback) {
            // Update the stored properties
            impl->properties.width = static_cast<unsigned int>(width);
            impl->properties.height = static_cast<unsigned int>(height);

            // Call the user's resize callback
            impl->resizeCallback(static_cast<unsigned int>(width), static_cast<unsigned int>(height));
        }
    }

    void Window::Impl::glfwKeyCallback(GLFWwindow *window, const int key, const int scancode, const int action, const int mods) {
        if (const auto* impl = static_cast<Window::Impl*>(glfwGetWindowUserPointer(window)); impl && impl->keyCallback) {
            impl->keyCallback(key, scancode, action, mods);
        }
    }

    void Window::Impl::glfwMouseCallback(GLFWwindow *window, const int button, const int action, const int mods) {
        if (const auto* impl = static_cast<Window::Impl*>(glfwGetWindowUserPointer(window)); impl && impl->mouseCallback) {
            impl->mouseCallback(button, action, mods);
        }
    }

}  // polykami::core::window