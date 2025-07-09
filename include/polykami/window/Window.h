//
// Created by niek on 2025/07/08.
//

#ifndef WINDOW_H
#define WINDOW_H

#include <memory>
#include <string>
#include <functional>

namespace polykami::window {

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

        bool initialize() const;
        void update() const;
        void shutdown() const;

        [[nodiscard]] bool shouldClose() const;
        void swapBuffers() const;

        [[nodiscard]] unsigned int getWidth() const;
        [[nodiscard]] unsigned int getHeight() const;
        void setSize(unsigned int width, unsigned int height) const;

        void setTitle(const std::string& title) const;
        void setVSync(bool enabled) const;

        [[nodiscard]] void* getNativeWindow() const;

        // Event callbacks
        using ResizeCallback = std::function<void(unsigned int, unsigned int)>;
        using KeyCallback = std::function<void(int, int, int, int)>;
        using MouseCallback = std::function<void(int, int, int)>;

        void setResizeCallback(const ResizeCallback &resizeCallback) const;
        void setKeyCallback(const KeyCallback &keyCallback) const;
        void setMouseCallback(const MouseCallback &mouseCallback) const;

    private:
        class Impl;
        std::unique_ptr<Impl> pImpl;
    };

}  // polykami::core::window

#endif //WINDOW_H
