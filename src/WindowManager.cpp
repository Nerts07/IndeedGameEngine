#include "WindowManager.h"

#include <iostream>
#include <inputs.h>
#include <assert.h>

GLFWwindow* WindowManager::window;
int WindowManager::width = 0;
int WindowManager::height = 0;


void WindowManager::init(int width, int height, const char* title)
{

	this->window = nullptr;
	this->monitor = nullptr;
	this->mode = nullptr;
	this->width = width;
	this->height = height;
	this->title = title;
	this->ypos = 0;
	this->xpos = 0;

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (!window) {
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}

	assert(window != NULL);
}

WindowManager::WindowManager()
{


}

void WindowManager::centerMonitor()
{
	// Get the primary monitor's video mode
	monitor = glfwGetPrimaryMonitor();
	mode = glfwGetVideoMode(monitor);

	// Calculate the position to center the window
	this->xpos = (mode->width - width) / 2;
	this->ypos = (mode->height - height) / 2;
}


void WindowManager::centerInit()
{
	glfwSetWindowPos(window, xpos, ypos);
}
//Inputs inputs;
//void CRS(GLFWwindow* window, double xpos, double ypos)
//{
//	inputs.cursor_Position_Callback(window, xpos, ypos);
//}
void WindowManager::makeContextCurrent() 
{
	glfwMakeContextCurrent(window);
	//glfwSetCursorPosCallback(window, CRS);
}


void viewport(GLFWwindow* window, int w, int h)
{
	glViewport(0, 0, w, h);

	WindowManager::width = w;
	WindowManager::height = h;
}

void WindowManager::loadGL()
{
	glfwSetFramebufferSizeCallback(window, viewport);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}
}

//void WindowManager::pollEvents()
//{
//	glfwPollEvents();
//}

void WindowManager::swapBuffs()
{
	glfwSwapBuffers(window);
}
bool WindowManager::gameLoop()
{
	return glfwWindowShouldClose(window);
}

int WindowManager::getWidth()
{
	return width;
}

int WindowManager::getHeight()
{
	return height;
}

GLFWwindow* WindowManager::getWindow()
{
	return window;
}

void WindowManager::vSync(bool enable)
{
	if (enable == true)
	{
		glfwSwapInterval(1);
	}
	else
	{
		glfwSwapInterval(0);
	}
}

void WindowManager::setCursor(bool enable)
{
	if (enable == true)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
	else
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
}

WindowManager::~WindowManager()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}