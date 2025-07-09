//
// Created by niek on 2025/07/08.
//

#include "polykami/core/window/Window.h"
#include "core/window/Window_Impl.h"

namespace polykami::core::window {
    Window::Window(const WindowProperties &props)
        : pImpl(std::make_unique<Impl>(props)) { }

    Window::~Window() {
        pImpl->shutdown();
    }

    Window::Window(Window && other) noexcept
        : pImpl(std::move(other.pImpl)) { }

    Window& Window::operator=(Window && other) noexcept {
        if (this != &other) {
            // Clean up current resources
            if (pImpl) {
                pImpl->shutdown();
            }

            // Transfer ownership
            pImpl = std::move(other.pImpl);
        }
        return *this;
    }

    bool Window::initialize() const {
        return pImpl->initialize();
    }

    void Window::update() const {
        pImpl->update();
    }

    void Window::shutdown() const {
        pImpl->shutdown();
    }

    bool Window::shouldClose() const {
        return pImpl->shouldClose();
    }

    void Window::swapBuffers() const {
        pImpl->swapBuffers();
    }

    unsigned int Window::getWidth() const {
        return pImpl->getWidth();
    }

    unsigned int Window::getHeight() const {
        return pImpl->getHeight();
    }

    void Window::setSize(const unsigned int width, const unsigned int height) const {
        pImpl->setSize(width, height);
    }

    void Window::setTitle(const std::string &title) const {
        pImpl->setTitle(title);
    }

    void Window::setVSync(const bool enabled) const {
        pImpl->setVSync(enabled);
    }

    void * Window::getNativeWindow() const {
        return pImpl->getNativeWindow();
    }

    void Window::setResizeCallback(const ResizeCallback &resizeCallback) const {
        pImpl->setResizeCallback(resizeCallback);
    }

    void Window::setKeyCallback(const KeyCallback &keyCallback) const {
        pImpl->setKeyCallback(keyCallback);
    }

    void Window::setMouseCallback(const MouseCallback &mouseCallback) const {
        pImpl->setMouseCallback(mouseCallback);
    }

}  // polykami::core::window