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
        void shutdown();

        [[nodiscard]] bool shouldClose() const;
        void swapBuffers();

        [[nodiscard]] unsigned int getWidth() const { return properties.width; }
        [[nodiscard]] unsigned int getHeight() const { return properties.height; }
        void setSize(unsigned int width, unsigned int height);

        void setTitle(const std::string& title);
        void setVSync(bool enabled);

        [[nodiscard]] void* getNativeWindow() const { return window; }

        void setResizeCallback(ResizeCallback callback);
        void setKeyCallback(KeyCallback callback);
        void setMouseCallback(MouseCallback callback);

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
