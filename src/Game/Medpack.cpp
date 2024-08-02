#include "Medpack.h"

Medpack::Medpack()
{
	this->addModel("res/Test/helthpack/healthPack.gltf");
	this->setScale(1.4, 1.8, 1.4);
	this->position.y = -1;
}

void Medpack::onUpdate(Timestep timestep)
{
	rotate(0, 50 * timestep, 0);
}

float Medpack::getDistanceFromCamera()
{
	return glm::distance(this->position, campos);
}

void Medpack::draw(Shader& shader, Camera& camera)
{
	this->campos = glm::vec3(camera.position.x, this->position.y, camera.position.z) / this->scale;
	GameObject::draw(shader, camera);
}
