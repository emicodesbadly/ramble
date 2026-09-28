#include <stdio.h>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "stb_image/stb_image.h"
#include "ramble/ramble.h"
#include "utils.h"


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
		printf("%sERROR:%s Failed to create GLFW window!\n", ANSI_BOLD_RED, ANSI_RESET);
		glfwTerminate();
		return 1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, on_window_resized);

	/* GLAD: load OpenGL function pointers */
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("%sERROR:%s Failed to load OpenGL function pointers!\n", ANSI_BOLD_RED, ANSI_RESET);
		return 1;
	}

	/*
	 * OpenGL expects (0,0) to be at the bottom left corner of an image,
	 * while images usually have (0,0) at the top left. This results in
	 * images being displayed upside-down.
	 * 
	 * To correct this, we vertically flip images on load.
	 */
	stbi_set_flip_vertically_on_load(true);

	Canvas::init(960, 540);

	/* DEBUG STUFF */
	Shader *shader = new Shader("shader", DEFAULT_TEXTURED_VERT, DEFAULT_TEXTURED_FRAG);

	int w, h, nch;
	unsigned char *data = stbi_load("resources/textures/missing.png", &w, &h, &nch, 0);
	Texture *texture = new Texture("missing", data, w, h, nch);

	TexturedRect *tr = new TexturedRect(vec2(0,0), shader, texture);

	/* Main Loop */
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		/* RENDERING START */

		Canvas::instance()->bind_and_clear();

		tr->render();

		Canvas::instance()->render(window);

		/* RENDERING END */

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	/* CLEANUP */
	delete texture;
	delete shader;

	Canvas::destroy();

	return 0;
}

void on_window_resized(GLFWwindow *window, int width, int height)
{
	/* Adjust viewport size */
	glViewport(0, 0, width, height);

	/* Adjust canvas to maintain aspect ratio */
	Canvas::instance()->on_window_resized(width, height);
}
