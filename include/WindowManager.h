#ifndef WindowManager_H
#define WindowManager_H

#include "GLload.h"

class WindowManager
{
public:
	WindowManager();
	~WindowManager();

	void init(int width, int height, const char* title);
	void centerMonitor();
	void centerInit();
	void makeContextCurrent();
	void loadGL();
	void swapBuffs();
	//void pollEvents();
	bool gameLoop();
	void vSync(bool enable);

	void setCursor(bool enable);

	int getWidth();
	int getHeight();
	GLFWwindow* getWindow();

	static GLFWwindow* window;
	static int width;
	static int height;

	//friend void viewport(GLFWwindow* window, int w, int h);
private:

	GLFWmonitor* monitor;
	const GLFWvidmode* mode;



	const char* title;

	//for centering window
	int xpos;
	int ypos;

	//void viewport(GLFWwindow* window, int w, int h);
};
#endif