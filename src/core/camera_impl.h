//
// Created by niek on 2025/07/10.
//

#ifndef CAMERA_IMPL_H
#define CAMERA_IMPL_H

#include "polykami/core/camera.h"

namespace polykami::core {

    class Camera::Impl {
    public:
        explicit Impl(glm::vec3 pos);

        void updateCameraVectors();
        [[nodiscard]] glm::mat4 getViewMatrix() const;

        void processMouseMovement(float xOffset, float yOffset, bool constrainPitch);
        void processKeyboardMovement(glm::vec3 direction, float deltaTime);

        glm::vec3 position, front, up, right{};
        float yaw, pitch, speed, fov, sensitivity;
    };

}  // polykami::core

#endif //CAMERA_IMPL_H
