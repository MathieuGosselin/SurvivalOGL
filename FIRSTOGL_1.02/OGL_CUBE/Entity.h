#pragma once

#include "Model.h"
#include "vmath.h"


class Entity
{
public:
	Entity(const char *ModelPath,vmath::vec3 _position);
	Entity(void);
	~Entity(void);

	Model model;
	vmath::vec3 Position;

	virtual void Update();
	virtual void Draw();

private:
	
	
};
