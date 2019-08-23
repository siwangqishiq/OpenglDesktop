#pragma once

#include "App.h"

class Triangle : public IApp {
private:
	GLfloat vertices[3 * 3] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};

	GLuint vao;
	GLuint vbo;

	GLuint programId;
public:
	virtual void init();
	virtual void update(int w, int h);
	virtual void onDestory();
	~Triangle();
};



