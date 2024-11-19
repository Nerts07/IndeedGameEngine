#include "Inputs.h"

#include <iostream>


using namespace std;

Inputs::Inputs()
{


	//this->win = window.getWindow();
	
}

//static Inputs& getInstance()
//{
//	static Inputs instance;
//	return instance;
//}

Inputs::~Inputs()
{
	delete[] keys;
	delete[] mouseButtons;
	delete[] frames;
}

void Inputs::init()
{

	this->keys = new bool[1024];
	this->mouseButtons = new bool[12];
	this->frames = new int[1024];

	memset(keys, 0, sizeof(bool) * 1024);
	memset(mouseButtons, 0, sizeof(bool) * 12);
	memset(frames, 0, sizeof(int) * 1024);


	//glfwSetInputMode(win, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
	glfwMakeContextCurrent(win);
	//glfwSetWindowUserPointer(win, this);
	glfwSetWindowUserPointer(win, this);

	glfwSetKeyCallback(win, keyCallback);
	glfwSetCursorPosCallback(win, cursor_Position_Callback);
	glfwSetMouseButtonCallback(win, mouseButtonCallback);
	glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}



void Inputs::toggleCursor(bool enable)
{
	if (enable == true)
	{
		glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
	if (enable == false)
	{
		glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

}


void Inputs::pollEvent()
{
	currentFrame++;
	glfwPollEvents();
}


/*
* Input callback functions
*/
//void Inputs::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
//{
//
//	if (action == GLFW_PRESS)
//	{
//		getInstance().keys[key] = true;
//		getInstance().frames[key] = getInstance().currentFrame;
//	}
//	else if (action == GLFW_RELEASE)
//	{
//		getInstance().keys[key] = false;
//		getInstance().frames[key] = getInstance().currentFrame;
//	}
//}
void Inputs::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Inputs* instance = static_cast<Inputs*>(glfwGetWindowUserPointer(window)); // Get instance
	if (action == GLFW_PRESS)
	{
		instance->keys[key] = true;
		instance->frames[key] = instance->currentFrame;
	}
	else if (action == GLFW_RELEASE)
	{
		instance->keys[key] = false;
		instance->frames[key] = instance->currentFrame;
	}
}

//void Inputs::cursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
//{
//	getInstance().mouseX = xpos;
//	getInstance().mouseY = ypos;
//
//	glfwGetCursorPos(window, &xpos, &ypos);
//}
// 
void Inputs::cursor_Position_Callback(GLFWwindow* window, double xpos, double ypos)
{
	Inputs* instance = static_cast<Inputs*>(glfwGetWindowUserPointer(window)); // Get instance	

	if (instance->firstMouse)
	{
		instance->lastX = xpos;
		instance->lastY = ypos;
		instance->firstMouse = false;
	}

	float xoffset = xpos - instance->lastX;
	float yoffset = instance->lastY - ypos; // Reversed since y-coordinates go from bottom to top

	instance->lastX = xpos;
	instance->lastY = ypos;

	//instance->cam.mouseCallback(window, xpos, ypos);
	instance->cam.processMouseMovemnt(xoffset, yoffset, true);

	glfwGetCursorPos(window, &xpos, &ypos);
	std::cout << "xpos: " << xpos << " ypos: " << ypos << std::endl;
}
//
//void Inputs::cursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
//{
//	Inputs* instance = static_cast<Inputs*>(glfwGetWindowUserPointer(window)); // Get instance
//
//
//	instance->mouseX = xpos;
//	instance->mouseY = ypos;
//
//
//
//	glfwGetCursorPos(window, &xpos, &ypos);
//	std::cout << "xpos: " << xpos << " ypos: " << ypos << std::endl;
//}

//void Inputs::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
//{
//	if (action == GLFW_PRESS)
//	{
//		getInstance().mouseButtons[button] = true;
//		getInstance().frames[button] = getInstance().currentFrame;
//	}
//	else if (action == GLFW_RELEASE)
//	{
//		getInstance().mouseButtons[button] = false;
//		getInstance().frames[button] = getInstance().currentFrame;
//	}
//}

void Inputs::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	Inputs* instance = static_cast<Inputs*>(glfwGetWindowUserPointer(window)); // Get instance
	if (action == GLFW_PRESS)
	{
		instance->mouseButtons[button] = true;
		instance->frames[button] = instance->currentFrame;
	}
	else if (action == GLFW_RELEASE)
	{
		instance->mouseButtons[button] = false;
		instance->frames[button] = instance->currentFrame;
	}
}

/*
* Input functions
*/
bool Inputs::pressed(int keycode)
{
	if (keycode < 0 || keycode >= 1024)
	{
		return false;
	}
	return keys[keycode];
}

bool Inputs::justPressed(int keycode)
{
	if (keycode < 0 || keycode >= 1024)
	{
		return false;
	}
	return keys[keycode] && frames[keycode] == currentFrame;
}

bool Inputs::clicked(int keycode)
{
	if (keycode < 0 || keycode >= 12)
	{
		return false;
	}
	return mouseButtons[keycode];
}

bool Inputs::justClicked(int keycode)
{
	if (keycode < 0 || keycode >= 12)
	{
		return false;
	}
	return mouseButtons[keycode] && frames[keycode] == currentFrame;
}

/*
* Getters
*/
double Inputs::getMouseX()
{
	return lastX;
}

double Inputs::getMouseY()
{
	return lastY;
}

int Inputs::getCurrentFrame()
{
	return currentFrame;
}

int* Inputs::getFrames()
{
	return frames;
}

bool* Inputs::getKeys()
{
	return keys;
}

bool* Inputs::getMouseButtons()
{
	return mouseButtons;
}