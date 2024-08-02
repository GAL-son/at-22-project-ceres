#ifndef OBJECT_CLASS_H
#define OBJECT_CLASS_H

#include "../Events/Event.h"
#include "../Core/Timestep.h"
#include "Camera.h"
#include "OpenGL/Shader.h"
#include "Object.h"

/**
 * @class Object
 * @brief Abstract class representing an object in the scene.
 */
class Object
{
public:
	glm::vec3 position; ///< The position of the object.
	glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f); ///< The scale of the object.
	glm::quat rotation = glm::quat(1.0f,0.0f, 0.0f, 0.0f); ///< The rotation of the object.
	glm::mat4 cameraMatrix = glm::mat4(1.0f); ///< The camera matrix of the object.

	/**
	 * @brief Draws the object using the specified shader and camera.
	 * @param shader The shader used for rendering.
	 * @param camera The camera used for rendering.
	 */
	virtual void draw(Shader& shader, Camera& camera) = 0;

	/**
	 * @brief Draws the object at the specified position and rotation.
	 * @param position The position at which to draw the object.
	 * @param rotation The rotation at which to draw the object.
	 */
	virtual void draw(glm::vec3 position, glm::vec3 rotation) {};

	/**
	 * @brief Updates the object based on the elapsed timestep.
	 * @param timestep The elapsed timestep since the last update.
	 */
	virtual void onUpdate(Timestep timestep) = 0;

	/**
	 * @brief Handles the specified event.
	 * @param event The event to handle.
	 */
	virtual void onEvent(Event& event) {};

	/**
	 * @brief Moves the object in the specified direction.
	 * @param direction The direction to move the object.
	 */
	void inline move(glm::vec3 direction) { position += direction; }

	/**
	 * @brief Sets the position of the object.
	 * @param position The new position of the object.
	 */
	void inline setPosition(glm::vec3 position) { this->position = position; }

	/**
	 * @brief Sets the position of the object using individual coordinates.
	 * @param x The x-coordinate of the new position.
	 * @param y The y-coordinate of the new position.
	 * @param z The z-coordinate of the new position.
	 */
	void setPosition(float x, float y, float z);

	/**
	 * @brief Sets the scale of the object using individual factors.
	 * @param x The scaling factor along the x-axis.
	 * @param y The scaling factor along the y-axis.
	 * @param z The scaling factor along the z-axis.
	 */
	void setScale(float x, float y, float z);

	/**
	 * @brief Moves the object along the x-axis.
	 * @param x The amount to move along the x-axis.
	 */
	void moveX(float x);

	/**
	 * @brief Sets the rotation of the object using quatermion.
	 * @param rotation New rotation quatermion.
	 */
	void inline setRotation(glm::quat rotation) { this->rotation = rotation; }

	/**
	 * @brief rotates the object using Euler angles.
	 * @param degx The rotation angle around the x-axis in degrees.
	 * @param degy The rotation angle around the y-axis in degrees.
	 * @param degz The rotation angle around the z-axis in degrees.
	 */
	void rotate(float degx, float degy, float degz);

	/**
	 * @brief Links the object to a camera.
	 * @param camera The camera to link to the object.
	 */
	void inline linkCamera(Camera& camera) { this->camera = &camera; }

	/**
	 * @brief Copies the position of the linked camera with an optional offset.
	 * @param offset The offset to apply to the copied camera position.
	 */
	void copyCameraPosition(glm::vec3 offset = glm::vec3(0.0f, 0.0f, 0.0f))
	{
		this->position = camera->position + offset;
	}

	/**
	 * @brief Sets the visibility of the object.
	 * @param value The visibility value to set.
	 */
	inline void setVisible(bool value) { this->isVisible = value; }

protected:
	std::vector<Object*> linkedObjects; ///< Objects linked to this object.
	
	Camera* camera = nullptr; ///< The linked camera.
	Shader* shader = nullptr; ///< The shader used for rendering.
	bool isVisible = true; ///< Flag indicating the visibility of the object.

	/**
	 * @brief Moves the linked objects along with this object.
	 */
	void moveLinkedObjects();
};

#endif // !OBJECT_CLASS_H
