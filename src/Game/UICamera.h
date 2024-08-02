#pragma once
#ifndef UI_CAMERA_H
#define UI_CAMERA_H

#include "../Renderer/Camera.h"

/**
 * @class UICamera
 * @brief Class representing a camera object designed to handle UI elements.
 */
class UICamera : public Camera
{
public:
    /**
     * @brief Constructor for UICamera.
     * @param widthpx The width of the camera viewport in pixels.
     * @param heightpx The height of the camera viewport in pixels.
     * @param nearPlane The distance to the near clipping plane.
     * @param farPlane The distance to the far clipping plane.
     * @param FOV The field of view in degrees.
     * @param position The initial position of the camera. Defaults to (0.0, 0.0, 0.0).
     */
	UICamera(int widthpx, int heightpx, float nearPlane, float FarPlane, float FOV, glm::vec3 position = glm::vec3(0.0, 0.0, 0.0)) : Camera(widthpx, heightpx, nearPlane, FarPlane, FOV, position) {};
	
    /**
     * @brief Destructor for UICamera.
     */
    ~UICamera();

    /**
     * @brief Function called on every update to update the UI camera.
     * @param timestep The time since the last update.
     */
	void onUpdate(Timestep timestep) override;

    /**
     * @brief Function called when an event occurs.
     * @param event The event that occurred.
     */
	void onEvent(Event& event) override;
};

#endif // !UI_CAMERA_H




