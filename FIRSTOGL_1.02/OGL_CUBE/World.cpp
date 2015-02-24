#include "World.h"


World::World(const char *filename, GLuint program)
{
	map.loadmap(filename);
	cam = new camera();
	spotlight = new SpotLight(program);

	uniforms.mvp = glGetUniformLocation(program,"mvp");
	uniforms.mv = glGetUniformLocation(program,"mv");
	uniforms.m = glGetUniformLocation(program,"m");
}

void World::Update()
{
	model = vmath::translate(-cam->position());
	mvp = cam->matrix() * model;

	glUniformMatrix4fv(uniforms.mvp, 1, GL_FALSE, mvp);
	glUniformMatrix4fv(uniforms.mv,1,GL_FALSE, cam->view() * model);
	glUniformMatrix4fv(uniforms.m,1,GL_FALSE, model);
	
	spotlight->update(model);
}

void World::Draw()
{
	for(int i = 0; i < 3; i++)
	{
		glBindVertexArray(map.VAO[i]);
		glBindTexture(GL_TEXTURE_2D,i+1);
		glDrawArrays(GL_TRIANGLES,0,200000);
	}
}


World::~World(void)
{
	map.~Map();
	delete cam;
	delete spotlight;
}
