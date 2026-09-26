#include <stdio.h>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "stb_image/stb_image.h"

void on_window_resized(GLFWwindow *window, int width, int height);

int main(void)
{
	/* GLFW: initialize & configure */
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* GLFW: create window */
	GLFWwindow *window = glfwCreateWindow(960, 540, "Ramble Game", NULL, NULL);

	if (window == NULL)
	{
		printf("ERROR: Failed to create GLFW window!\n");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, on_window_resized);

	/* GLAD: load OpenGL function pointers */
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("ERROR: Failed to load OpenGL function pointers!\n");
		return -1;
	}

	/*
	 * OpenGL expects 0.0 on the y axis to be on the bottom side of an image,
	 * while images usually have 0.0 on the top side. This results in images
	 * being displayed upside-down.
	 * 
	 * To correct this, we vertically flip images on load.
	 */
	stbi_set_flip_vertically_on_load(true);

	/* Main Loop */
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	return 0;
}

void on_window_resized(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}
