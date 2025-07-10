//
// Created by niek on 2025/07/10.
//

#include "polykami/core/camera.h"
#include "core/camera_impl.h"

namespace polykami::core {
    Camera::Camera(glm::vec3 startPosition)
        : yaw(0), pitch(0), speed(0), fov(0), sensitivity(0), position(), front(), up(), right(),
          impl(std::make_unique<Impl>(startPosition)) {
    }

    Camera::~Camera() = default;

    void Camera::processMouseMovement(const float xOffset, const float yOffset, const bool constrainPitch) const {
        impl->processMouseMovement(xOffset, yOffset, constrainPitch);
    }

    void Camera::processKeyboardMovement(const glm::vec3 direction, const float deltaTime) const {
        impl->processKeyboardMovement(direction, deltaTime);
    }

    void Camera::updateCameraVectors() const {
        impl->updateCameraVectors();
    }

    glm::mat4 Camera::getViewMatrix() const {
        return impl->getViewMatrix();
    }

    void Camera::setPosition(const glm::vec3 position) {
        this->position = position;
    }

    glm::vec3 Camera::getPosition() const {
        return position;
    }
}  // polykami::core