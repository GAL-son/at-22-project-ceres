#include "Gun.h"

#include "../Core/Input.h"

Gun::Gun()
{
	this->addModel("res/Test/TestGun/dddd.gltf");
}

void Gun::onUpdate(Timestep timestep)
{
	lookCameraKey(timestep);
	if (camera != nullptr)
	{
		copyCameraPosition({ 0.0f, -0.2f, 0.0f });
	}
}

bool Gun::lookCameraKey(float seconds)
{
	float sensitivity = 10 * seconds;
	float degRoationY = 0;

	if (Input::isKeyPressed(GLFW_KEY_O))
		degRoationY += (sensitivity * 10);
	if (Input::isKeyPressed(GLFW_KEY_P))
		degRoationY -= (sensitivity * 10);

	rotate(0, degRoationY, 0);

	return true;
}

void Gun::draw(Shader& shader, Camera& camera)
{
	camerap = &camera;
	GameObject::draw(shader, camera);
}

void Gun::rotateCamera(Timestep ts)
{
	if (camerap == nullptr) return;
	glm::vec2 desiredDirection = glm::normalize(glm::vec2(camerap->orientation.x, camerap->orientation.z));
	glm::vec2 yourDirection(direction.x, direction.z);

	float currentAngle = glm::degrees(glm::angle(yourDirection, desiredDirection));

	if (currentAngle > 2)
	{

		float yAngle = 0.0;
		glm::vec3 testRotation = glm::normalize(glm::rotateY(direction, glm::radians((float)1.0)));

		if (glm::degrees(glm::angle(glm::vec2(testRotation.x, testRotation.z), desiredDirection)) < currentAngle)
		{
			yAngle = currentAngle * 0.5;
		}
		else
		{
			yAngle = currentAngle * (-0.5);
		}
		this->rotate(0.0, -currentAngle, 0.0);
		direction = glm::normalize(glm::rotateY(direction, glm::radians(currentAngle)));
	}
}