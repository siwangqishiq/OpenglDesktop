#include "App.h"

GLuint CompileShader(GLenum shaderType, const char* shaderSource) {
	GLuint shader = glCreateShader(shaderType);
	if (shader == 0) {
		std::cout << "create shader fail:" << shaderSource << std::endl;
		glDeleteShader(shader);
		return 0;
	}
	const char* shaderCode = shaderSource;
	if (shaderCode == nullptr) {
		printf("load shader code from %s fail\n", shaderSource);
		std::cout << "load shader code from " << shaderSource << " failed" << std::endl;
		glDeleteShader(shader);
		return 0;
	}

	glShaderSource(shader, 1, &shaderCode, nullptr);
	glCompileShader(shader);

	GLint compileResult = GL_TRUE;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);
	if (compileResult == GL_FALSE) {
		char szLog[1024] = { 0 };
		GLsizei logLen = 0;
		glGetShaderInfoLog(shader, 1024, &logLen, szLog);
		printf("Compile Shader fail error log: %s \nshader code:\n%s\n", szLog, shaderCode);
		glDeleteShader(shader);
		shader = 0;
	}
	return shader;
}

GLuint CreateGPUProgram(const char* vsShaderSource, const char* fsShaderSource) {
	GLuint vsShader = CompileShader(GL_VERTEX_SHADER, vsShaderSource);
	GLuint fsShader = CompileShader(GL_FRAGMENT_SHADER, fsShaderSource);

	//Attach
	GLuint program = glCreateProgram();
	glAttachShader(program, vsShader);
	glAttachShader(program, fsShader);

	//Link
	glLinkProgram(program);

	//Clear
	glDetachShader(program, vsShader);
	glDetachShader(program, fsShader);
	glDeleteShader(vsShader);
	glDeleteShader(fsShader);

	//check error
	GLint linkResult = GL_TRUE;
	glGetProgramiv(program, GL_LINK_STATUS, &linkResult);
	if (linkResult == GL_FALSE) {
		char szLog[1024] = { 0 };
		GLsizei logLen = 0;
		glGetProgramInfoLog(program, 1024, &logLen, szLog);
		printf("Link program fail error log: %s \nvs shader code:\n%s\nfs shader code:\n%s\n", szLog, "vertexSource", "fragmentSource");
		glDeleteShader(program);
		program = 0;
	}

	std::cout << "program = " << program << std::endl;
	return program;
}