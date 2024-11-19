#include <fps.h>

FPS::FPS() 
: fpsStartTime(std::chrono::steady_clock::now())

{
	
}

void FPS::fpsUpdate()
{
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
	fps = 1 / deltaTime;
}

void FPS::fpsMax(int fps)
{
	int ms = 1000 / fps;
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}
