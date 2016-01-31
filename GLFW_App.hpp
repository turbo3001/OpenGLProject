#pragma once
#include "GLFW_Window.hpp" //Our GLFW Window
#include <ctime>

class GLFW_App
{
protected:
	GLFW_Window mWindow;
public:
	GLFW_Window& window(){ return mWindow; }
	
	GLFW_App(int width = 640, int height = 480)
	{
		/*---------------------------------------------------------------------------------------------
		 *	Initialise GLFW
		 *---------------------------------------------------------------------------------------------*/
		if (!glfwInit()) exit(EXIT_FAILURE);
		printf("glfw initialised \n");

		mWindow.create(this, width, height);

		/*---------------------------------------------------------------------------------------------
		*	Initialise GLEW
		*---------------------------------------------------------------------------------------------*/
		glewExperimental = true;

		GLenum glewError = glewInit();
		if (glewError != GLEW_OK) {
			printf("glew init error\n%s\n", glewGetErrorString(glewError));
			return;
		}

		if (!GLEW_VERSION_2_1) {
			printf("OpenGL 2.1 is not supported!\n");
			return;
		}

		//Get Version String
		const GLubyte * p = glGetString(GL_VERSION);
		printf("Graphics Driver: %s", p);

		//Get GLSL Version String
		const GLubyte * q = glGetString(GL_SHADING_LANGUAGE_VERSION);
		printf("GLSL Version: %s", q);

		if (GLEW_ARB_vertex_array_object) {
			printf("genVertexArrays supported\n");
		}
		if (GLEW_APPLE_vertex_array_object) {
			printf("genVertexArrayAPPLE supported\n");
		}

		/*-----------------------------------------------------------------------------
		*  Some Good Defaults to Start with: enable Alpha Blending and Depth Testing
		*-----------------------------------------------------------------------------*/
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glLineWidth(3);               //<-- Thicken lines so we can see 'em clearly

	}

	void start() {
		clock_t begin = clock();
		clock_t prev = begin;

		int framesSinceLastSecond = 0;
		double timeSinceLastSecond = 0.0;

		while (!mWindow.shouldClose()) {
			mWindow.setViewport();

			glClearColor(0.6, 0.8, 0.92, 1);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			onDraw();

			mWindow.swapBuffers();
			glfwPollEvents();
			clock_t currentFrame = clock();
			double timesinceBeg = (currentFrame - begin)/CLOCKS_PER_SEC;
			double frameTime = (currentFrame - prev)/CLOCKS_PER_SEC;

			framesSinceLastSecond++;
			timeSinceLastSecond += frameTime;
			if (timeSinceLastSecond > 1) {
				printf("%i FPS", framesSinceLastSecond);
				timeSinceLastSecond = 0.0;
				framesSinceLastSecond = 0;
			}
			printf("Frames Time %f", frameTime);
			printf("Time Since Start %f", timesinceBeg);

		}
	}

	~GLFW_App()
	{
		glfwTerminate();
	}

	virtual void onDraw() {}

	virtual void onMouseMove(int x, int y) {}

	virtual void onMouseDown(int button, int action) {}

	virtual void onKeyDown(int key, int action) {}

};

