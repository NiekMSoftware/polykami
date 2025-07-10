//
// Created by niek on 2025/07/10.
//

#include "core/camera_impl.h"
#include <bits/stl_algo.h>

namespace polykami::core {
    Camera::Impl::Impl(const glm::vec3 pos)
        : position{pos}, front{glm::vec3{0.0f, 0.0f, -1.0f}}, up(glm::vec3{0.0f, 1.0f, 0.0f}),
          yaw{YAW}, pitch {PITCH}, speed{SPEED},
          fov{FOV}, sensitivity(SENSITIVITY) {
        updateCameraVectors();
    }

    void Camera::Impl::updateCameraVectors() {
        glm::vec3 f;
        f.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        f.y = sin(glm::radians(pitch));
        f.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        front = glm::normalize(f);
        right = glm::normalize(glm::cross(front, glm::vec3{0.0f, 1.0f, 0.0f}));
        up = glm::normalize(glm::cross(right, front));
    }

    glm::mat4 Camera::Impl::getViewMatrix() const {
        return glm::lookAt(position, position + front, up);
    }

    void Camera::Impl::processMouseMovement(float xOffset, float yOffset, const bool constrainPitch) {
        xOffset *= sensitivity;
        yOffset *= sensitivity;

        yaw += xOffset;
        pitch += yOffset;

        if (constrainPitch) {
            pitch = std::clamp(pitch, -89.0f, 89.0f);
        }

        updateCameraVectors();
    }

    void Camera::Impl::processKeyboardMovement(const glm::vec3 direction, const float deltaTime) {
        const float velocity = speed * deltaTime;
        position += direction * velocity;
    }
}  // polykami::core