//
// Created by niek on 2025/07/08.
//

#include "Window_Impl.h"

namespace polykami::core::window {
    Window::Impl::Impl(const WindowProperties &properties) {
        if (!initialize()) {
            throw std::runtime_error("Failed to initialize Window");
        }
    }

    Window::Impl::~Impl() {
    }

    bool Window::Impl::initialize() {
    }

    void Window::Impl::update() {
    }

    void Window::Impl::shutdown() {
    }

    bool Window::Impl::shouldClose() const {
    }

    void Window::Impl::swapBuffers() {
    }

    void Window::Impl::setSize(unsigned int width, unsigned int height) {
    }

    void Window::Impl::setTitle(const std::string &title) {
    }

    void Window::Impl::setVSync(bool enabled) {
    }

    void Window::Impl::setResizeCallback(ResizeCallback callback) {
    }

    void Window::Impl::setKeyCallback(KeyCallback callback) {
    }

    void Window::Impl::setMouseCallback(MouseCallback callback) {
    }

    void Window::Impl::glfwResizeCallback(GLFWwindow *window, int width, int height) {
    }

    void Window::Impl::glfwKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    }

    void Window::Impl::glfwMouseCallback(GLFWwindow *window, int button, int action, int mods) {
    }
}  // polykami::core::window