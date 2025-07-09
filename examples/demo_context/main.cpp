//
// Created by niek on 2025/07/09.
//

#include <iostream>
#include <polykami/polykami.h>

int main() {
    try {
        polykami::core::Polykernel kernel;
    } catch (...) {
        std::cerr << "Failed to initialize Polykernel" << std::endl;
    }
}