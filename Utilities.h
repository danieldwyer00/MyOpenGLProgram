#pragma once
#include <glad/glad.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include <ctime>
#include <sstream>
#include <string>

static const char* extract_version(const char* full)
{
	std::string p1 = full;
	static std::string p2;
	p2.clear();
	p2 = p1.substr(
		p1.find_last_of("/\\") + 1, //after last slash
		(p1.length() - p1.find_last_of("/\\")) - (p1.length() - (p1.find_last_of(".")) + 1) // up to last dot
	);
	return p2.c_str();
}


static void write_log(const char* msg)
{
	// Get the timestamp for the current date and time
	time_t timestamp;
	time(&timestamp);

	std::ofstream logs;
	logs.open("our_log.txt", std::ofstream::app | std::ofstream::out);
	logs  << "\n[" << ctime(&timestamp) << "] " << msg;
	logs.close();
}

void printGLinfo()
{
	const GLubyte* vendor = glGetString(GL_VENDOR);
	printf("GL Vendor: %s\n", vendor);

	const GLubyte* renderer = glGetString(GL_RENDERER);
	printf("GL Renderer: %s\n", renderer);

	const GLubyte* version = glGetString(GL_VERSION);
	printf("GL Version: %s\n", version);

	GLint major, minor;
	glGetIntegerv(GL_MAJOR_VERSION, &major);
	glGetIntegerv(GL_MINOR_VERSION, &minor);
	printf("GL Version (integer): %d.%d\n", major, minor);

	const GLubyte* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
	printf("GLSL Version: %s\n", glslVersion);
}

std::string ReadToString(const std::string& filename) {
	std::ifstream file(filename);
	if (!file) {
		throw std::runtime_error("Failed to open file: " + filename);
	}

	std::ostringstream contents;
	contents << file.rdbuf();
	return contents.str();
}