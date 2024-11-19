#include "GLload.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Shaders.h"
#include "Textures.h"
#include "fps.h"
#include "WindowManager.h"
#include "Inputs.h"
#include "Cam.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <chrono>
#include <iostream>
#include <vector>
#include <thread>

using namespace std;
float lastFrame = 0.0f;
float deltaTime = 0.0f;
std::chrono::steady_clock::time_point startTime;

float speed = 2.5f;
bool pPressed = false;
bool showCursor = false;
bool isZoomed = false;

GLfloat vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};
vector<GLuint> indices = {
    0, 1, 3,
    1, 2, 3
};

Inputs input;
void CRS(GLFWwindow* window, double xpos, double ypos)
{
    input.cursor_Position_Callback(window, xpos, ypos);
}

int main()
{
    WindowManager window;
    window.init(1024, 720, "Minecraft");
    window.centerMonitor();
    window.makeContextCurrent();
    glfwSetCursorPosCallback(window.getWindow(), CRS);

    window.loadGL();


    Shaders shader(RESOURCES_PATH"vert.glsl", RESOURCES_PATH"frag.glsl");
    // VAO, VBO, EBO setup
    
    VAO vao;
    vao.bind();

    VBO vbo;
    vbo.vboInit(vertices, sizeof(vertices));
    EBO ebo(indices);

    vao.linkAttrib(vbo, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
    vao.linkAttrib(vbo, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));

    vao.unbind();
    vbo.unbind();
    ebo.unbind();

    // Texture setup
    Texture stena(RESOURCES_PATH"gr.png", Texture::Filter::LINEAR);
    shader.useShader();
    shader.setInt("tex", 0);
    stena.uniform(shader, "tex", 0);
 
    window.centerInit();
    Inputs inputs;
	inputs.init();

    FPS fps;
    startTime = std::chrono::steady_clock::now();

    glm::mat4 model = glm::mat4(1.0f);

    model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);


    Cam camera;
    camera.setFov(105.0f);
    camera.setCamMode(Cam::CamMode::PERSPECTIVE);

	GLFWwindow* win = window.getWindow();
	
    while (!window.gameLoop())
	{
        glClear(GL_COLOR_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (inputs.clicked(MOUSE_BUTTON_1))
        {
            glClearColor(0.2f, 0.4f, 0.3f, 1.0f);
            //camera.processMouseMovemnt(inputs.getMouseX(), inputs.getMouseY(), true);
        }
        if (inputs.pressed(KEY_P))
        {
			camera.setCamMode(Cam::CamMode::PERSPECTIVE);
            //inputs.cursor_Position_Callback(window.getWindow(), inputs.getMouseX(), inputs.getMouseY());

        }
        if (inputs.pressed(KEY_O))
        {
			camera.setCamMode(Cam::CamMode::ORTHOGRAPHIC);
        }

		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

        float vertSin = sin((float)glfwGetTime()) * 0.003f;

		fps.fpsUpdate();

#ifdef DEBUG
		cout << "fps: " << fps.getFPS() << endl;

#endif // DEBUG

		window.vSync(true);


        // Render begin

        stena.bind();
        shader.useShader();

        if (inputs.justPressed(KEY_L))
        {
			pPressed = !pPressed;
           
        }
        if (pPressed)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		}
		else
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}

        if (inputs.justPressed(KEY_ESCAPE))
        {
			showCursor = !showCursor;
           
        }
        if (showCursor)
        {
            inputs.toggleCursor(true);
        }
		else
		{
			inputs.toggleCursor(false);
		}

        if (inputs.pressed(KEY_W))
        {
    		camera.moveInput(Cam::FORWARD, deltaTime);
        }
        if (inputs.pressed(KEY_S))
        {
    		camera.moveInput(Cam::BACKWARD, deltaTime);
        }
        if (inputs.pressed(KEY_A))
        {
    		camera.moveInput(Cam::LEFT, deltaTime);
        }
        if (inputs.pressed(KEY_D))
        {
    		camera.moveInput(Cam::RIGHT, deltaTime);
        }
        if (inputs.pressed(KEY_SPACE))
        {
    		camera.moveInput(Cam::UP, deltaTime);
        }
        if (inputs.pressed(KEY_LEFT_SHIFT))
        {
    		camera.moveInput(Cam::DOWN, deltaTime);
        }

        if (inputs.justPressed(KEY_C))
        {
			isZoomed = !isZoomed;

        }

		if (isZoomed)
		{
			camera.setFov(20.0f);
		}
		else
		{
			camera.setFov(75.0f);
		}


        model = glm::rotate(model, glm::radians(15.0f * deltaTime), glm::vec3(0.0f, 1.0f * deltaTime, 0.0f));
		model = glm::translate(model, glm::vec3(vertSin, vertSin, vertSin));

		//unsigned int transformLoc = glGetUniformLocation(shader.shaderProgram, "transform");
		//glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

		glm::mat4 view = camera.getView();

		shader.setMatrix4fv("projection", camera.getProjection());
		shader.setMatrix4fv("view", camera.getView());
        shader.setMatrix4fv("model", model);

        vao.bind();
        glDrawArrays(GL_TRIANGLES, 0, 36);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // Render end
        
        window.swapBuffs();
        inputs.pollEvent();
    }
    //delete window;
    return 0;
}
