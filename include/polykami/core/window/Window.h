//
// Created by niek on 2025/07/08.
//

#ifndef WINDOW_H
#define WINDOW_H

#include <memory>
#include <string>
#include <functional>

namespace polykami::core::window {

    struct WindowProperties {
        std::string title = "Polykami Window";

        unsigned int width = 800;
        unsigned int height = 600;

        bool vsync = true;
        bool resizable = true;
    };

    class Window {
    public:
        explicit Window(const WindowProperties& props = WindowProperties{});
        ~Window();

        // Non-copyable but moveable
        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;
        Window(Window&&) noexcept;
        Window& operator=(Window&&) noexcept;

        bool initialize();
        void update();
        void shutdown();

        bool shouldClose() const;
        void swapBuffers();

        unsigned int getWidth() const;
        unsigned int getHeight() const;
        void setSize(unsigned int width, unsigned int height);

        void setTitle(const std::string& title);
        void setVSync(bool enabled);

        void* getNativeWindow() const;

        // Event callbacks
        using ResizeCallback = std::function<void(unsigned int, unsigned int)>;
        using KeyCallback = std::function<void(int, int, int, int)>;
        using MouseCallback = std::function<void(int, int, int)>;

        void setResizeCallback(ResizeCallback resizeCallback);
        void setKeyCallback(KeyCallback keyCallback);
        void setMouseCallback(MouseCallback mouseCallback);

    private:
        class Impl;
        std::unique_ptr<Impl> pImpl;
    };

}  // polykami::core::window

#endif //WINDOW_H
