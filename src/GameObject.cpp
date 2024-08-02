#include "GameObject.h"
#include "GameObject.h"

GameObject::~GameObject()
{
	if (activeModel != nullptr)
	{
		delete activeModel;
	}
}

void GameObject::addModel(const char* path)
{
	this->activeModel = new Model(path);
}

void GameObject::draw(Shader& shader, Camera& camera)
{
	if (!isVisible) return;
	activeModel->Draw(shader, camera, position, rotation, scale);
}

Model& GameObject::getModel()
{
	return *(activeModel);
}
