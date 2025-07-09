//
// Created by niek on 2025/07/08.
//

#ifndef WINDOW_IMPL_H
#define WINDOW_IMPL_H

#include "polykami/core/window/Window.h"
#include <GLFW/glfw3.h>

namespace polykami::core::window {

    class Window::Impl {
    public:
        explicit Impl(const WindowProperties& properties);
        ~Impl();

        bool initialize();
        void update();
        void shutdown() const;

        [[nodiscard]] bool shouldClose() const;
        void swapBuffers() const;

        [[nodiscard]] unsigned int getWidth() const { return properties.width; }
        [[nodiscard]] unsigned int getHeight() const { return properties.height; }
        void setSize(unsigned int width, unsigned int height);

        void setTitle(const std::string& title) const;
        void setVSync(bool enabled);

        [[nodiscard]] void* getNativeWindow() const { return window; }

        void setResizeCallback(const ResizeCallback &callback);
        void setKeyCallback(const KeyCallback &callback);
        void setMouseCallback(const MouseCallback &callback);

    private:
        GLFWwindow* window;
        WindowProperties properties;

        ResizeCallback resizeCallback;
        KeyCallback keyCallback;
        MouseCallback mouseCallback;

        // static GLFW callbacks
        static void glfwResizeCallback(GLFWwindow* window, int width, int height);
        static void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void glfwMouseCallback(GLFWwindow* window, int button, int action, int mods);
    };

}  // polykami::core::window

#endif //WINDOW_IMPL_H
