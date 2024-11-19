/*
* Author: Isa Heydarli
* Date: 2024-10-19 00:39
* License: MIT
* Purpose: Inputs/Events class for OpenGL
* Note: This class is a part of the OpenGL project (my own Game Engine)
* Note: refactored class of my old Input.cpp file, made it more object-oriented and more readable
*/

#ifndef INPUTS_H
#define INPUTS_H

#pragma once

#include "GLload.h"
#include "KeyMacros.h"
#include "WindowManager.h"
#include "Cam.h"

#include <vector>
#include <cstring>

class Inputs
{
public:
	Inputs();
	~Inputs();

	void init();
	void pollEvent();
	void toggleCursor(bool enable);

	/*
	* Input callback functions
	*/
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
	static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

	static void cursor_Position_Callback(GLFWwindow* window, double xpos, double ypos);

	/*
	* Input functions
	*/
	bool pressed(int keycode); //means that the key is being pressed(hold until you release)
	bool justPressed(int keycode); //means that the key was pressed in the current frame
	bool clicked(int keycode); //means that the key is being clicked(hold until you release)
	bool justClicked(int keycode); //means that the key was clicked in the current frame

	/*
	* Getters
	*/
	double getMouseX();
	double getMouseY();

	int getCurrentFrame();
	int* getFrames();

	bool* getKeys();
	bool* getMouseButtons();

	
	/*
	* Setters
	*/

private:
	bool* keys; //array of keys 1024 blocks of memory (1024 keys)
	bool* mouseButtons; //array of mouse buttons 12 blocks of memory (12 buttons)
	int* frames; //array of frames 1024 blocks of memory (1024 frames)

	Cam cam;

	float lastX = WindowManager::width / 2.0f;
	float lastY = WindowManager::height / 2.0f;

	bool firstMouse = true;

	double mouseX, mouseY;
	int currentFrame;
	GLFWwindow* win = WindowManager::window;

	//Inputs(Inputs const&) = delete; // copy constructor, prevent copy
	//void operator=(Inputs const&) = delete; // prevent assignment

};
#endif