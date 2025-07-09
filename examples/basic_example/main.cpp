//
// Created by niek on 2025/07/09.
//

#include <iostream>
#include <polykami/polykami.h>

int main() {
    try {
        polykami::core::polykernel kernel;

        while (!kernel.getWindow()->shouldClose()) {
            kernel.getWindow()->update();
            kernel.clearFrame();
            kernel.getWindow()->swapBuffers();
        }
        
    } catch (...) {
        std::cerr << "Failed to initialize Polykernel" << std::endl;
    }
}