//Include OpenGL for graphics and Glfw for windowing
#include <stdlib.h>
#define GLEW_STATIC
#include <GL/glew.h>
#include "GLFW/glfw3.h"
#include <iostream>

using namespace std;


int main(int argc, char * argv[]) {
	
	int width = 800, height = 600;

	GLFWwindow * window;
	if (!glfwInit()) exit(EXIT_FAILURE);
	window = glfwCreateWindow(width, height, "glfw", NULL, NULL);
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);

	glewExperimental = true; // This flag helps prevent errors with modern OpenGL
							 //	LR: It also allows access to new features!

	GLenum glewError = glewInit();
	if (glewError != GLEW_OK) {
		printf("glew init error\n%s\n", glewGetErrorString(glewError));
	}

	if (!GLEW_VERSION_2_1) {
		printf("OpenGL 2.1 is not supported!\n");
		return false;
	}

	//Get Version String
	const GLubyte * p = glGetString(GL_VERSION);
	cout << "Graphics Driver: " << p << endl;
	
	//Get GLSL Version String
	const GLubyte * q = glGetString(GL_SHADING_LANGUAGE_VERSION);
	cout << "GLSL Version" << q << endl;

	if (GLEW_ARB_vertex_array_object) {
		printf("genVertexArrays supported\n");
	}
	if (GLEW_APPLE_vertex_array_object) {
		printf("genVertexArrayAPPLE supported\n");
	}

	while (!glfwWindowShouldClose(window)) {
		glViewport(0, 0, width, height);
		glClearColor(1, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Put Draw code here;

		glfwSwapBuffers(window);
		glfwPollEvents();

	}


	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;

}