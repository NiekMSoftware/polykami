//
// Created by niek on 2025/07/09.
//

#include "polykami/core/Polykernel.h"
#include "core/Polykernel_Impl.h"
#include <iostream>

namespace polykami::core {

    Polykernel::Polykernel() : pImpl(std::make_unique<Impl>()) {
        try {
            // initialize OpenGL
            pImpl->initializeOpenGL();

            // initialize window
            WindowProperties props{};
            pWindow = std::make_unique<Window>(props);

            // set viewport
            pImpl->setViewport(static_cast<int>(pWindow->getWidth()), static_cast<int>(pWindow->getHeight()));

        } catch (const std::exception& e) {
            std::cerr << "Failed to initialize Polykernel: " << e.what() << std::endl;
            throw;
        } catch (...) {
            std::cerr << "Unknown exception thrown" << std::endl;
            throw;
        }
    }

    Polykernel::~Polykernel() {
        pImpl->cleanup();
    }

    Polykernel::Polykernel(Polykernel&& other) noexcept
        : pWindow(std::move(other.pWindow)), pImpl(std::move(other.pImpl)) { }

    Polykernel & Polykernel::operator=(Polykernel&& other) noexcept {
        if (this != &other) {
            // Clean up current resources
            if (pImpl) {
                pImpl->cleanup();
            }

            // Move resources
            pImpl = std::move(other.pImpl);
            pWindow = std::move(other.pWindow);
        }
        return *this;
    }

    void Polykernel::initializeOpenGL() const {
        pImpl->initializeOpenGL();
    }

    void Polykernel::cleanup() const {
        pImpl->cleanup();
    }

    void Polykernel::setViewport(const int width, const int height) const {
        pImpl->setViewport(width, height);
    }

    void Polykernel::clearFrame(const float r, const float g, const float b, const float a) const {
        pImpl->clearFrame(r, g, b, a);
    }

}  // polykami::core