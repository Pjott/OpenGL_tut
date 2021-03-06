// GL_App.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
//#define GLEW_STATIC

const GLint WIDTH = 800, HEIGHT = 600;

GLuint VAO, VBO, shader;

//vertex shader
static const char* vShader = "										\n\
#version 330														\n\
																	\n\
layout (location = 0) in vec3 pos;									\n\
																	\n\
void main() {														\n\
	gl_Position = vec4(0.4 * pos.x, 0.4 * pos.y, pos.z, 1.0);		\n\
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

//function to attaching shaders to the program
void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType) {

	GLuint theShader = glCreateShader(shaderType);
	const GLchar* theCode[1];
	theCode[0] = shaderCode;
	GLint codeLenght[1];
	codeLenght[0] = strlen(shaderCode);
	glShaderSource(theShader, 1, theCode, codeLenght);
	glCompileShader(theShader);
	//checking errors
	GLint result = 0;
	GLchar eLog[1024] = { 0 };
	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result) {
		glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
		printf("Error compiling the %d shader: '%s'\n", shaderType, eLog);
		return;
	}
	//attach shader
	glAttachShader(theProgram, theShader);
}

//creating a shader program
void CompileShaders() {
	shader = glCreateProgram();
	//checking if shader crates
	if (!shader) {
		printf("Error at creating program");
		return;
	}
	//attaching shaders to the program
	AddShader(shader, vShader, GL_VERTEX_SHADER);
	AddShader(shader, fShader, GL_FRAGMENT_SHADER);
	//validate the program
	GLint result = 0;
	GLchar eLog[1024] = { 0 };
	//link the program- creates executables from shaders and links them together
	glLinkProgram(shader);
	//getting information about proper link program
	glGetProgramiv(shader, GL_LINK_STATUS, &result);
	if (!result) {
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("Error linking the program: '%s'\n", eLog);
		return;
	}
	//validate the program
	glValidateProgram(shader);
	glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
	if (!result) {
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("Error validating the program: '%s'\n", eLog);
		return;
	}
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

	CreateTrinagle();
	CompileShaders();

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		glUseProgram(shader);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
		//closing program
		glUseProgram(0);
		//drawing opengl stuff
		glfwSwapBuffers(window);
	}

	glfwTerminate();

	return EXIT_SUCCESS;
}
