#ifndef CAM_H
#define CAM_H

#pragma once

#include "GLload.h"
#include "WindowManager.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Cam {
public:

    enum Camera_Movement {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT,
        UP,
        DOWN
    };

    enum CamMode {
        PERSPECTIVE,
        ORTHOGRAPHIC
    };


    Cam();


    void setPosition(glm::vec3 position);
    void setAspect(float aspect);
    float getAspect() const;
    void setFov(float fov);
    glm::mat4 setCamMode(CamMode mode);
    glm::mat4 getView();
    glm::mat4 getProjection();
    void moveInput(Camera_Movement direction, float deltaTime);
    void processMouseMovemnt(float x_offset, float y_offset, GLboolean constrainPitch = true);

private:

    void updateVectors();

    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;

    float yaw;
    float pitch;
    float zoom;
    float aspect;
    float fov;

    float movementSpeed;
    float mouseSensitivity;

    float lastX;
    float lastY;

    CamMode mode;

    static constexpr float YAW = -90.0f;
    static constexpr float PITCH = 0.0f;
    static constexpr float ZOOM = 45.0f;
    static constexpr float SPEED = 2.5f;
    static constexpr float SENSITIVITY = 0.1f;
};

#endif // CAM_H
