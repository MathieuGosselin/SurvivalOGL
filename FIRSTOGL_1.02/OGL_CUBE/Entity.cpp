#include "Entity.h"
#include "MGstream.h"


Entity::Entity(const char *ModelPath,vmath::vec3 _position)
{
	if(!model.LoadModel(ModelPath))
	{
		DBOUT("Error Loading Model");
	}
	else
	{
		Position = _position;
	}
}

Entity::Entity(void)
{

}

void Entity::Draw()
{
	model.Draw();
}

void Entity::Update()
{

}

Entity::~Entity(void)
{
}
