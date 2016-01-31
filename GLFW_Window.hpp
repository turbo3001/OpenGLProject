#pragma once
//Include OpenGL for graphics and Glfw for windowing
#include <stdlib.h>
#define GLEW_STATIC
#include <GL/glew.h>
#include "GLFW/glfw3.h"
#include <iostream>

struct Interface
{
	static void * app;
	
	template<class APPLICATION>
	static void OnKeyDown(GLFWwindow* window, int key, int scancode, int action, int mods) {
		((APPLICATION*)(app))->onKeyDown(key, action);
	}

	template<class APPLICATION>
	static void OnMouseMove(GLFWwindow* window, double x, double y) {
		((APPLICATION*)(app))->onMouseMove(x, y);
	}

	template<class APPLICATION>
	static void onMouseDown(GLFWwindow* window, int button, int action, int mods) {
		((APPLICATION*)(app))->onMouseDown(button, action);
	}
};

void * Interface::app;

class GLFW_Window
{
protected:
	GLFWwindow * mWindow;
	Interface mInterface;

	int mWidth, mHeight;

public:

	int width() { return mWidth; }
	int height() { return mHeight; }
	float ratio() { return (float)mWidth / mHeight; }

	GLFW_Window()
	{
	}

	template<class APPLICATION>
	void create(APPLICATION * app, int width, int height, const char * name = "default") {

		mInterface.app = app;

		mWidth = width; mHeight = height;

		mWindow = glfwCreateWindow(width, height, NULL, NULL);

		if (!mWindow) {
			glfwTerminate();
			exit(EXIT_FAILURE);
		}

		glfwMakeContextCurrent(mWindow);
		glfwSwapInterval(1);

		glfwSetKeyCallback(mWindow, Interface::OnKeyDown<APPLICATION>);
		glfwSetCursorPosCallback(mWindow, Interface::OnMouseMove<APPLICATION>);
		glfwSetMouseButtonCallback(window, Interface::onMouseDown<APPLICATION>);

	}

	void setViewport() {
		glfwGetFramebufferSize(mWindow, &mWidth, &mHeight);
		glViewport(0, 0, mWidth, mHeight);
	}

	bool shouldClose() {
		return glfwWindowShouldClose(mWindow);
	}

	void swapBuffers() {
		glfwSwapBuffers(mWindow);
	}

	void destroy() {
		glfwDestroyWindow(mWindow);
	}

	~GLFW_Window()
	{
		destroy();
	}
};

