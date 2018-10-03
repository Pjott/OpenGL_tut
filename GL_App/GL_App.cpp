// GL_App.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
//#define GLEW_STATIC

const GLint WIDTH = 800, HEIGHT = 600;

GLuint VAO, VBO;

//vertex shader
static const char* vShader = "							\n\
#version 330											\n\
														\n\
layout (location = 0) in vec3 pos;						\n\
														\n\
void main() {											\n\
	gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);		\n\
}";	

//fragment shader
static const char* fShader ="							\n\
#version 330											\n\
														\n\
out vec4 colour;										\n\
														\n\
void main() {											\n\
	colour = vec4(1.0, 0.0, 0.0, 1.0);					\n\
}";

void CreateTrinagle() {
	GLfloat vertices[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};

	//VAO & binding
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	//VBO & binding
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//attach the vertex data to that VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//define the attribute pointer formatting
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//enable the attribute pointer
	glEnableVertexAttribArray(0);
	//unbind the VAO and VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

int main()
{

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	//create window
	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Learn OpenGL", nullptr, nullptr);

	int screenWidth, screenHeight;
	//accurete representation of window
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	if (nullptr == window) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialize GLEW" << std::endl;

		return EXIT_FAILURE;
	}

	glViewport(0, 0, screenHeight, screenWidth);

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//drawing opengl stuff
		glfwSwapBuffers(window);
	}

	glfwTerminate();

	return EXIT_SUCCESS;
}
