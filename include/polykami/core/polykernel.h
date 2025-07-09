//
// Created by niek on 2025/07/09.
//

#ifndef POLYKERNEL_H
#define POLYKERNEL_H

#include <memory>
#include "polykami/window/window.h"

// === namespace inclusion ===
using namespace polykami::window;

namespace polykami::core {

    class polykernel {
    public:
        polykernel();
        ~polykernel();

        // Non-copyable but moveable
        polykernel(const polykernel&) = delete;
        polykernel& operator=(const polykernel&) = delete;
        polykernel(polykernel&&) noexcept;
        polykernel& operator=(polykernel&&) noexcept;

        // === OpenGL loader functions
        void initializeOpenGL() const;
        void cleanup() const;

        // === OpenGL functions
        void setViewport(int width, int height) const;
        void clearFrame(float r = 0.2f, float g = 0.3f, float b = 0.4f, float a = 1.0f) const;

        // === Getters ===
        [[nodiscard]] Window* getWindow() const { return pWindow.get(); }

    private:
        // === context objects ===
        std::unique_ptr<Window> pWindow;

        // === pImpl idiom ===
        class Impl;
        std::unique_ptr<Impl> pImpl;
    };

}  // polykami::core

#endif //POLYKERNEL_H
