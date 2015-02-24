#pragma once
#include "Map.h"
#include "camera.h"
#include "SpotLight.h"

class World
{
public:

	struct{
		GLint mvp;
		GLint mv;
		GLint m;
	}uniforms;

	//Variables
	vmath::mat4 mvp;
	vmath::mat4 model;
	
	camera *cam;

	//function
	World(const char *filename,GLuint program);

	void Draw();
	void Update();

	

	~World(void);

private:
	Map map;
	SpotLight *spotlight;
};

