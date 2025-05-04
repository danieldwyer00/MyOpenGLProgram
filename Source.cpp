#define _CRT_SECURE_NO_WARNINGS

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Callbacks.h"
#include "Utilities.h"
#include "Vertex.h"
#include <vector>
#include "OpenGLLoader.h"
#include "OpenGLDraw.h"
#include "Input.h"

int main(int argc, char** argv)
{
	glfwSetErrorCallback(glfw_error_callback);
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	GLFWwindow* window = glfwCreateWindow(800, 600, extract_version(argv[0]), nullptr, nullptr);
	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glfwSetWindowCloseCallback(window, glfw_window_close_callback);
	glfwSetFramebufferSizeCallback(window, glfw_framebuffer_size_callback);

	glClearColor(.2f, .2f, .6f, 0.f);
	std::vector<DrawDetails> ourDrawDetails;
	{
		//Create object to display points
		std::vector<Vertex> obj_pts;
		obj_pts.emplace_back(.5f, -.5f, 0.f);
		obj_pts.emplace_back(-.5f, -.5f, 0.f);
		obj_pts.emplace_back(0.f, 0.5f, 0.f);

		std::vector<uint32_t> elem = { 0,1,2 };

		//Upload Data to Grpahics Card
		ourDrawDetails.push_back(UploadMesh(obj_pts, elem));
	}
	

	while (!glfwWindowShouldClose(window))
	{
		//Handle Keypress
		ProcessInput(window);
		glClear(GL_COLOR_BUFFER_BIT);
		//render object
		Draw(ourDrawDetails);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	//Unload data from grpahics card
	UnloadMesh(ourDrawDetails);

	glfwTerminate();
	return 0;
}