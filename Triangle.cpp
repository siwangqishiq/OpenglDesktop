#include "Triangle.h"

void Triangle::init() {
	std::string vsShader = 
		"#version 330 core \n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main() { \n"
		"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}";
	std::string fragShader = 
		"#version 330 core \n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\n\0";

	programId = CreateGPUProgram(vsShader.c_str() , fragShader.c_str());
	
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	glBindVertexArray(0);
}

void Triangle::update(int w, int h) {
	glUseProgram(programId);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Triangle::onDestory() {
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
}

Triangle::~Triangle(){
	std::cout << "Triangle deconstruct" << std::endl;
}

