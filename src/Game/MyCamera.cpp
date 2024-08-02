
#include "../Engine.h"
#include "../Core/Timestep.h"
#include "../Core/Input.h"

#include "MyCamera.h"

void MyCamera::onUpdate(Timestep timestep)
{
	moveCamera(timestep);
	lookCameraKey(timestep);
	updateMatrix();
}

bool MyCamera::moveCamera(float seconds)
{
	float speed = 20 * seconds;

	glm::vec3 move;
	if (Input::isKeyPressed(GLFW_KEY_W))
		move += (speed * (this->orientation));
	if (Input::isKeyPressed(GLFW_KEY_S))
		move += (speed * -(this->orientation));
	if (Input::isKeyPressed(GLFW_KEY_A))
		move += (speed * -glm::normalize(glm::cross(this->orientation, this->up)));
	if (Input::isKeyPressed(GLFW_KEY_D))
		move += (speed * glm::normalize(glm::cross(this->orientation, this->up)));

	if (position.x > 55.0f)
	{
		move.x = 0;
		position.x = 55;
	}
	if (position.x < -55.0f)
	{
		move.x = 0;
		position.x = -55;
	}
	if (position.z > 55.0f)
	{
		move.z = 0;
		position.z = 55;
	}
	if (position.z < -55.0f)
	{
		move.z = 0;
		position.z = -55;
	}

	position = position + move;

	return true;
}

bool MyCamera::lookCameraKey(float seconds)
{
	float sensitivity = 10 * seconds;
	float degRoationY = 0;

	if (Input::isKeyPressed(GLFW_KEY_O))
		degRoationY += (sensitivity * 10);
	if (Input::isKeyPressed(GLFW_KEY_P))
		degRoationY -= (sensitivity * 10);

	orientation = glm::rotate(orientation, glm::radians(degRoationY), up);

	return true;
}

void MyCamera::lookCamera()
{
	if (!Input::isKeyPressed(GLFW_KEY_LEFT_SHIFT))
	{
		glfwSetInputMode(Engine::get().getWindow().getGLFWWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		return;
	}
	glfwSetInputMode(Engine::get().getWindow().getGLFWWindow(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	float mouseX = Input::getMouseX();

	int width = widthpx;
	int height = heightpx;

	float sensitivity = 100;

	float rotY = sensitivity * (float)(mouseX - (width / 2)) / width;

	orientation = glm::rotate(orientation, glm::radians(-rotY), up);

	glfwSetCursorPos(Engine::get().getWindow().getGLFWWindow(), (width / 2), (height / 2));
}
