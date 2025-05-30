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
#include "GLSLShaderLoader.h"
#include <iostream>
#include <random>
#include "QueryShader.h"
#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>




int main(int argc, char** argv)
{
	glfwSetErrorCallback(glfw_error_callback);
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);


	GLFWwindow* window = glfwCreateWindow(1920, 1200, extract_version(argv[0]), nullptr, nullptr);
	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	printGLinfo();

	glfwSetWindowCloseCallback(window, glfw_window_close_callback);
	glfwSetFramebufferSizeCallback(window, glfw_framebuffer_size_callback);

    #include <string>  

	const std::string vertShaderSource = ReadToString("..\\OpenGLTest\\VertexShader.glsl");
	const std::string fragShaderSource = ReadToString("..\\OpenGLTest\\FragmentShader.glsl");

	const char* vertshader = vertShaderSource.c_str();
	const char* fragshader = fragShaderSource.c_str();
	

	
	unsigned int mainShader = LoadShader(vertshader, fragshader);
	glClearColor(0.f, 0.f, 0.f, 0.f);
	std::vector<DrawDetails> ourDrawDetails;

	{
		const float posData[] = {
			-0.8f, -0.8f, 0.0f,
			0.8f, -0.8f, 0.0f,
			0.0f, 0.8f, 0.0f
		};
		const float colorData[] = {
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 1.0f
		};

		const GLuint elems[] = {0,1,2};
		//Upload Data to Grpahics Card
		ourDrawDetails.push_back(UploadMesh(posData, colorData, sizeof(posData)/sizeof(posData[0]),
			elems, sizeof(elems)/sizeof(elems[0])));
	}
	//std::default_random_engine generator;
	//std::uniform_real_distribution<float> distribution(0.f,1.f);

	QueryAttribs(mainShader);
	QueryUniforms(mainShader);

	double prev_time = glfwGetTime();
	while (!glfwWindowShouldClose(window))
	{
		double current_time = glfwGetTime();
		double dt = current_time - prev_time;
		prev_time = current_time;
		//Handle Keypress
		ProcessInput(window);
		glClear(GL_COLOR_BUFFER_BIT);
		//render object
		glUseProgram(mainShader);

		glm::mat4 finalModelMatrix = glm::mat4(1);
		finalModelMatrix = glm::translate(finalModelMatrix, glm::vec3(sin((float)glfwGetTime())/2, cos((float)glfwGetTime()) / 2,0));
		finalModelMatrix = glm::rotate(finalModelMatrix,(float)glfwGetTime(), glm::vec3(0.f, 1.f, 0.f));
		finalModelMatrix = glm::scale(finalModelMatrix, glm::vec3(.5));
		GLuint location = glGetUniformLocation(mainShader, "uModelMatrix");
		glUniformMatrix4fv(location, 1, GL_FALSE, &finalModelMatrix[0][0]);
		for(const auto& thing : ourDrawDetails)
		{
			Draw(ourDrawDetails);
		}

		Draw(ourDrawDetails);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	//Unload data from grpahics card
	UnloadMesh(ourDrawDetails);

	glfwTerminate();
	return 0;
}