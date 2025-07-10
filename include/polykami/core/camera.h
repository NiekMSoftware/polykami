//
// Created by niek on 2025/07/10.
//

#ifndef CAMERA_H
#define CAMERA_H

#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace polykami::core {

    constexpr float YAW = -90.0f;
    constexpr float PITCH = 0.0f;
    constexpr float SPEED = 1.0f;
    constexpr float FOV = 60.0f;
    constexpr float SENSITIVITY = 0.1f;

    class Camera {
    public:
        explicit Camera(glm::vec3 startPosition = glm::vec3(0.0f));
        ~Camera();

        void processMouseMovement(float xOffset, float yOffset, bool constrainPitch = true) const;
        void processKeyboardMovement(glm::vec3 direction, float deltaTime) const;
        void updateCameraVectors() const;
        [[nodiscard]] glm::mat4 getViewMatrix() const;

        void setPosition(glm::vec3 position);
        [[nodiscard]] glm::vec3 getPosition() const;

    private:
        // === start of properties ===
        // euler angles
            float yaw;
            float pitch;
        // camera options
            float speed;
            float fov;
            float sensitivity;
        // === end of properties ===

        // === attributes ===
        glm::vec3 position;
        glm::vec3 front;
        glm::vec3 up;
        glm::vec3 right;

        // === pImpl idiom ===
        class Impl;
        std::unique_ptr<Impl> impl;
    };

}  // polykami::core

#endif //CAMERA_H
