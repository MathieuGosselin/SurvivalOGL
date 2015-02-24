#pragma once
#include "lodepng.h"
#include "sb6.h"
#include "vmath.h"

using namespace std;

class Map
{
public:
	GLfloat fQuad[108];
	//GLfloat vTex[72];
	GLfloat vNormal[108];
	GLuint VAO[3];
	Map(void);

	bool loadmap(const char *filename);


	~Map(void);

private:
	
	GLuint VBO[3];
	GLuint VBOTexture;
	GLuint VBOnormal[3];
	void createmap(std::vector<unsigned char> &img,unsigned width, unsigned height);
	void calculNormalVertex(GLfloat *vTex, int index, int indexVBO);
};

