//
// Created by niek on 2025/07/08.
//

#include "polykami/window/window.h"
#include "window/Window_Impl.h"
#include <stdexcept>

namespace polykami::window {
    window::window(const WindowProperties &props)
        : pImpl(std::make_unique<Impl>(props)) {
        if (!initialize()) {
            throw std::runtime_error("Failed to initialize window");
        }
    }

    window::~window() {
        pImpl->shutdown();
    }

    window::window(window && other) noexcept
        : pImpl(std::move(other.pImpl)) { }

    window& window::operator=(window && other) noexcept {
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

    bool window::initialize() const {
        return pImpl->initialize();
    }

    void window::update() const {
        pImpl->update();
    }

    void window::shutdown() const {
        pImpl->shutdown();
    }

    bool window::shouldClose() const {
        return pImpl->shouldClose();
    }

    void window::swapBuffers() const {
        pImpl->swapBuffers();
    }

    unsigned int window::getWidth() const {
        return pImpl->getWidth();
    }

    unsigned int window::getHeight() const {
        return pImpl->getHeight();
    }

    void window::setSize(const unsigned int width, const unsigned int height) const {
        pImpl->setSize(width, height);
    }

    void window::setTitle(const std::string &title) const {
        pImpl->setTitle(title);
    }

    void window::setVSync(const bool enabled) const {
        pImpl->setVSync(enabled);
    }

    void * window::getNativeWindow() const {
        return pImpl->getNativeWindow();
    }

    void window::setResizeCallback(const ResizeCallback &resizeCallback) const {
        pImpl->setResizeCallback(resizeCallback);
    }

    void window::setKeyCallback(const KeyCallback &keyCallback) const {
        pImpl->setKeyCallback(keyCallback);
    }

    void window::setMouseCallback(const MouseCallback &mouseCallback) const {
        pImpl->setMouseCallback(mouseCallback);
    }

}  // polykami::core::window