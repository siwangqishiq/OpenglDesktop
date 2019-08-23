#include <GL/glew.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h>

#include "App.h"

class MainRun : public IApp {
private:
	Vertex vertices[3] =
	{
		{ -0.6f, -0.4f, 1.f, 0.f, 0.f },
		{ 0.6f, -0.4f, 0.f, 1.f, 0.f },
		{ 0.f,  0.6f, 0.f, 0.f, 1.f }
	};

	const char* vertex_shader_text =
		"#version 330\n"
		"uniform mat4 MVP;\n"
		"attribute vec3 vCol;\n"
		"attribute vec2 vPos;\n"
		"varying vec3 color;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = MVP * vec4(vPos, 0.0, 1.0);\n"
		"   color = vCol;\n"
		"}\n";

	const char* fragment_shader_text =
		"#version 330\n"
		"varying vec3 color;\n"
		"void main()\n"
		"{\n"
		"    gl_FragColor = vec4(1.0f , 0.0f , 1.0f, 1.0f);\n"
		"}\n";

	GLuint vertex_buffer, vertex_shader, fragment_shader, program;
	GLint mvp_location, vpos_location, vcol_location;

public:
	void init(){
		glGenBuffers(1, &vertex_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		program = CreateGPUProgram(vertex_shader_text , fragment_shader_text);

		mvp_location = glGetUniformLocation(program, "MVP");
		vpos_location = glGetAttribLocation(program, "vPos");
		vcol_location = glGetAttribLocation(program, "vCol");

		glEnableVertexAttribArray(vpos_location);
		glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE,
			sizeof(vertices[0]), (void*)0);
		glEnableVertexAttribArray(vcol_location);
		glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE,
			sizeof(vertices[0]), (void*)(sizeof(float) * 2));
	}

	void update(int w, int h){
		float ratio = w / (float)h;

		mat4x4 m, p, mvp;

		mat4x4_identity(m);
		mat4x4_rotate_Z(m, m, (float)glfwGetTime());
		mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
		mat4x4_mul(mvp, p, m);
		glUseProgram(program);
		glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*)mvp);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

	void onDestory() {
	}
};