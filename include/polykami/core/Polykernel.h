//
// Created by niek on 2025/07/09.
//

#ifndef POLYKERNEL_H
#define POLYKERNEL_H

#include <memory>
#include "polykami/window/Window.h"

// === namespace inclusion ===
using namespace polykami::window;

namespace polykami::core {

    class Polykernel {
    public:
        Polykernel();
        ~Polykernel();

        // Non-copyable but moveable
        Polykernel(const Polykernel&) = delete;
        Polykernel& operator=(const Polykernel&) = delete;
        Polykernel(Polykernel&&) noexcept;
        Polykernel& operator=(Polykernel&&) noexcept;

        // === OpenGL loader functions
        void initializeOpenGL() const;
        void cleanup() const;

        // === OpenGL functions
        void setViewport(int width, int height) const;
        void clearFrame(float r = 0.2f, float g = 0.3f, float b = 0.4f, float a = 1.0f) const;

    private:
        // === context objects ===
        std::unique_ptr<Window> pWindow;

        // === pImpl idiom ===
        class Impl;
        std::unique_ptr<Impl> pImpl;
    };

}  // polykami::core

#endif //POLYKERNEL_H
