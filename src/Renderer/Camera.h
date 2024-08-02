#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <vector>

#include "../Renderer/OpenGL/Shader.h"
#include "../Core/Timestep.h"
#include "../Events/Event.h"

/**
 * @class Camera
 * @brief Represents a camera in the scene.
 */
class Camera
{
public:
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f); ///< The position of the camera.
	glm::vec3 orientation = glm::vec3(0.0f, 0.0f, -1.0f); ///< The orientation of the camera.
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f); ///< The up direction of the camera.
	glm::mat4 cameraMatrix = glm::mat4(1.0f); ///< The camera matrix.

	int widthpx, heightpx; ///< The width and height of the camera viewport.
	float nearPlane, farPlane; ///< The near and far planes of the camera's view frustum.
	float FOVdeg; ///< The field of view in degrees.

	/**
	 * @brief Constructor for Camera.
	 * @param widthpx The width of the camera viewport.
	 * @param heightpx The height of the camera viewport.
	 * @param nearPlane The near plane of the camera's view frustum.
	 * @param farPlane The far plane of the camera's view frustum.
	 * @param FOV The field of view in degrees.
	 * @param position The initial position of the camera.
	 */
	Camera(int widthpx, int heightpx, float nearPlane, float FarPlane, 
		float FOV = 45.0f, 
		glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f));

	/**
	 * @brief Updates the camera matrix.
	 */
	void Matrix(Shader& shader, const char* uniform);

	/**
	 * @brief Updates the camera matrix.
	 */
	void updateMatrix();

	/**
	 * @brief Called when the camera needs to update its state.
	 * @param timestep The timestep for the update.
	 */
	virtual void onUpdate(Timestep timestep) {};

	/**
	 * @brief Called when the camera receives an event.
	 * @param event The event received.
	 */
	virtual void onEvent(Event& event) {};	
};

#endif // !CAMERA_CLASS_H
