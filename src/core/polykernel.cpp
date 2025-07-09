//
// Created by niek on 2025/07/09.
//

#include "polykami/core/polykernel.h"
#include "core/Polykernel_Impl.h"
#include <iostream>

namespace polykami::core {

    polykernel::polykernel() : pImpl(std::make_unique<Impl>()) {
        try {
            // initialize OpenGL
            pImpl->initializeOpenGL();

            // initialize window
            WindowProperties props{};
            pWindow = std::make_unique<Window>(props);

            // load GLAD
            pImpl->loadGLAD();

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

    polykernel::~polykernel() {
        pImpl->cleanup();
    }

    polykernel::polykernel(polykernel&& other) noexcept
        : pWindow(std::move(other.pWindow)), pImpl(std::move(other.pImpl)) { }

    polykernel & polykernel::operator=(polykernel&& other) noexcept {
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

    void polykernel::initializeOpenGL() const {
        pImpl->initializeOpenGL();
    }

    void polykernel::cleanup() const {
        pImpl->cleanup();
    }

    void polykernel::setViewport(const int width, const int height) const {
        pImpl->setViewport(width, height);
    }

    void polykernel::clearFrame(const float r, const float g, const float b, const float a) const {
        pImpl->clearFrame(r, g, b, a);
    }

}  // polykami::core