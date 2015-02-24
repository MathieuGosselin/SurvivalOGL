#pragma once

#include "sb6.h"
#include <vector>

class Model
{
public:
	Model(void);
	~Model(void);

	void Draw();
	bool LoadModel(const char *filename);

	GLuint numFace;
	
	GLuint VAOM;

private:
	std::vector<GLfloat> array_vertex;
	std::vector<GLfloat> array_vTexture;
	std::vector<GLfloat> array_vNormal;

	std::vector<GLfloat> array_vertexToVBO;
	std::vector<GLfloat> array_vTextureToVBO;
	std::vector<GLfloat> array_vNormalToVBO;
	

	GLuint VBOM;
	GLuint VBOtex;
	GLuint VBOnorm;
};

