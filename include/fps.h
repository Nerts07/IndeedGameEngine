#ifndef FPS_H
#define FPS_H

#include "GLload.h"
#include <chrono>
#include <thread>
#include <iostream>

class FPS
{
public:
	FPS();
	void fpsUpdate();
	int getFPS() { return fps; }
	void fpsMax(int fps);
private:
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;
	std::chrono::steady_clock::time_point fpsStartTime;
	int fps;

};

#endif