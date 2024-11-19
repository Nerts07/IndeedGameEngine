#include "Cam.h"
#include "WindowManager.h"

#include <iostream>

Cam::Cam() :
position(glm::vec3(0.0f, 0.0f, 3.0f)),
front(glm::vec3(0.0f, 0.0f, -1.0f)),
up(glm::vec3(0.0f, 1.0f, 0.0f)),
right(glm::vec3(0.0f)),
yaw(YAW), pitch(PITCH),
movementSpeed(SPEED), 
mouseSensitivity(SENSITIVITY),
zoom(ZOOM)

{
	this->yaw = YAW;
	this->pitch = PITCH;
	this->movementSpeed = SPEED;
	this->mouseSensitivity = SENSITIVITY;
	this->zoom = ZOOM;
	this->lastX = WindowManager::width / 2.0f;
	this->lastY = WindowManager::height / 2.0f;

	updateVectors();
}

void Cam::setPosition(glm::vec3 position)
{
	this->position = position;
}

void Cam::setAspect(float aspect)
{
	this->aspect = (float)WindowManager::width / (float)WindowManager::height;
}
//float Cam::getAspect()
//{
//	return aspect;
//}
void Cam::setFov(float fov)
{
	this->fov = fov;
}

glm::mat4 Cam::setCamMode(CamMode mode)
{
	if (mode == PERSPECTIVE)
	{
		this->mode = PERSPECTIVE;
		return glm::perspective(glm::radians(fov), aspect, 0.01f, 100.0f);
	}
	else if (mode == ORTHOGRAPHIC)
	{
		float orthoScale = 1.0f;
		this->mode = ORTHOGRAPHIC;
		return  glm::ortho(-aspect * orthoScale, aspect * orthoScale, -orthoScale, orthoScale, 0.001f, 100.0f);
	}
	return glm::mat4(1.0f);
}

glm::mat4 Cam::getView()
{
	return glm::lookAt(position, position + front, up);
}

glm::mat4 Cam::getProjection()
{
	this->aspect = (float)WindowManager::width / (float)WindowManager::height;
	return setCamMode(mode);
}

void Cam::moveInput(Camera_Movement direction, float deltaTime)
{
	float velocity = movementSpeed * deltaTime;
	if (direction == FORWARD)
		position += front * velocity;
	if (direction == BACKWARD)
		position -= front * velocity;
	if (direction == LEFT)
		position -= right * velocity;
	if (direction == RIGHT)
		position += right * velocity;
	if (direction == UP)
		position += up * velocity;
	if (direction == DOWN)
		position -= up * velocity;
}

void Cam::updateVectors() 
{
	glm::vec3 Front;
	Front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	Front.y = sin(glm::radians(pitch));
	Front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(Front);

	this->right = glm::normalize(glm::cross(front, this->up));
	this->up = glm::normalize(glm::cross(this->right, front));
}


void Cam::processMouseMovemnt(float x_offset, float y_offset, GLboolean constrainPitch) {

	x_offset *= mouseSensitivity;
	y_offset *= mouseSensitivity;
	this->yaw += x_offset;
	this->pitch += y_offset;

	if (constrainPitch) {
		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;
	}
	updateVectors();
}

//void Cam::mouseCallback(GLFWwindow* window, double xpos, double ypos) {
//	if (firstMouse) {
//		lastX = xpos;
//		lastY = ypos;
//		firstMouse = false;
//	}
//	float xoffset = xpos - lastX;
//	float yoffset = lastY - ypos;
//	lastX = xpos;
//	lastY = ypos;
//	cam.processMouse(xoffset, yoffset);
//}