//
// Created by niek on 2025/07/09.
//

#ifndef POLYKERNEL_IMPL_H
#define POLYKERNEL_IMPL_H

#include "polykami/core/Polykernel.h"

namespace polykami::core {

    class Polykernel::Impl {
    public:
        Impl();
        ~Impl();

        void initializeOpenGL();
        void loadGLAD();
        void cleanup();

        // === OpenGL functions
        void setViewport(int width, int height) const;
        void clearFrame(float r, float g, float b, float a) const;

    private:
        bool initialized;
    };

}  // polykami::core

#endif //POLYKERNEL_IMPL_H
