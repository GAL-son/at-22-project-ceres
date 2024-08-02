#include "Object.h"

void Object::setPosition(float x, float y, float z)
{
	this->position.x = x;
	this->position.y = y; 
	this->position.z = z;
}

void Object::setScale(float x, float y, float z)
{
	scale.x = x;
	scale.y = y;
	scale.z = z;
}

void Object::moveX(float x)
{
	position.x += x;
}

void Object::rotate(float degx, float degy, float degz)
{
	glm::vec3 rot(glm::radians(degx), glm::radians(degy), glm::radians(degz));
	rotation = glm::normalize(rotation * glm::quat(rot));
}

void Object::moveLinkedObjects()
{
	for (Object* object : linkedObjects)
	{
		//object->draw(this->position, this->rotation); 
		// TODO: Add parameters to draw function
	}
}