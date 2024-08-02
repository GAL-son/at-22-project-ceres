#include "Bullet.h"

Bullet::Bullet(Light* light, glm::vec3 direction)
{
	this->addModel("res/Test/Bullet/Bullet.gltf");
	this->direction = glm::vec3(direction.x, 0.0, direction.z);
	this->light = light;
	setVisible(true);
}

void Bullet::onUpdate(Timestep ts) 
{
	light->setPosition(this->position);
	this->move(glm::normalize(direction) * (speed * ts));
}

void Bullet::disable()
{
	light->discard();
}
