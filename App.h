#ifndef __APP_H__
#define __APP_H__

#include <GL/glew.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "linmath.h"

const GLuint WIDTH = 800, HEIGHT = 600;

struct Vertex {
	float x, y;
	float r, g, b;
};

class IApp {
public:
	virtual void init() = 0;
	virtual void update(int w , int h) = 0;
	virtual void onDestory() = 0;
	virtual ~IApp() {
	}
};

GLuint CompileShader(GLenum shaderType, const char* shaderSource);

GLuint CreateGPUProgram(const char* vsShaderSource, const char* fsShaderSource);

#endif // 
