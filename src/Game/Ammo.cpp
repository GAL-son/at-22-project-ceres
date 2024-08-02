#include "Ammo.h"

Ammo::Ammo()
{
	this->addModel("res/Test/Ammobox/Ammobox.gltf");
	this->setScale(1.4, 1.8, 1.4);
	this->position.y = -1;
}

void Ammo::onUpdate(Timestep timestep)
{
	rotate(0, 50 * timestep, 0);
}

float Ammo::getDistanceFromCamera()
{
	return glm::distance(this->position, campos);
}

void Ammo::draw(Shader& shader, Camera& camera)
{
	this->campos = glm::vec3(camera.position.x, this->position.y, camera.position.z) / this->scale;
	GameObject::draw(shader, camera);
}