// HelloTemplate.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

#define GLEW_STATIC  
#include <GL/glew.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h>

#include "linmath.h"
#include "App.h"
#include "Run.hpp"
#include "Triangle.h"

using namespace std;

// Function prototypes    
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);


int main(){
	std::cout << "你好 世界 OpenGL 3.3" << std::endl;

	// Init GLFW    
	glfwInit();

	// Set all the required options for GLFW    
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object that we can use for GLFW's functions    
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Hello World", nullptr, nullptr);//窗口
	//GLFWwindow* window = glfwCreateWindow(640, 480, "My Title", glfwGetPrimaryMonitor(), NULL); //全屏

	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	// Set the required callback functions    
	glfwSetKeyCallback(window, key_callback);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions    
	glewExperimental = GL_TRUE;

	// Initialize GLEW to setup the OpenGL Function pointers    
	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	// Define the viewport dimensions    
	glViewport(0, 0, WIDTH, HEIGHT);

	//MainRun mainRun;
	//mainRun.init();

	IApp* triangle = new Triangle();
	triangle->init();

	// Game loop    
	while (!glfwWindowShouldClose(window)){
		float ratio;
		int width, height;
		
		glfwGetFramebufferSize(window, &width, &height);
		ratio = width / (float)height;
		glViewport(0, 0, width, height);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//mainRun.update(width , height);
		triangle->update(width , height);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}//end while

	triangle->onDestory();
	//mainRun.onDestory();
	delete triangle;


	// Terminate GLFW, clearing any resources allocated by GLFW.    
	glfwTerminate();

	return 0;
}

// Is called whenever a key is pressed/released via GLFW    
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode){
	std::cout << key << std::endl;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}