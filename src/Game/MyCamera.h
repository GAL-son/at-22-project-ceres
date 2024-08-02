#pragma once
#ifndef MY_CAMERA_H
#define MY_CAMERA_H

#include "../Renderer/Camera.h"

/**
 * @class MyCamera
 * @brief Class representing a custom camera object.
 */
class MyCamera : public Camera{
public:
    /**
     * @brief Constructor for MyCamera.
     * @param widthpx The width of the camera viewport in pixels.
     * @param heightpx The height of the camera viewport in pixels.
     * @param nearPlane The distance to the near clipping plane.
     * @param farPlane The distance to the far clipping plane.
     * @param FOV The field of view in degrees.
     * @param position The initial position of the camera. Defaults to (0.0, 0.0, 0.0).
     */
	MyCamera(int widthpx, int heightpx, float nearPlane, float FarPlane, float FOV, glm::vec3 position = glm::vec3(0.0, 0.0, 0.0)) : Camera(widthpx, heightpx, nearPlane, FarPlane, FOV, position) {}

    /**
     * @brief Function called on every update to update the camera.
     * @param timestep The time since the last update.
     */
	void onUpdate(Timestep timestep) override;

    /**
    * @brief Move the camera.
    * @param seconds The time in seconds.
    * @return True if the camera was moved successfully, false otherwise.
    */
	bool moveCamera(float seconds);

    /**
     * @brief Perform camera rotation based on keyboard input.
     * @param seconds The time in seconds.
     * @return True if the camera rotation was performed successfully, false otherwise.
     */
	bool lookCameraKey(float seconds);

    // TODO: DECIDE IF DELETE
    /**
     * @brief Perform camera look based on mouse input.
     */
	void lookCamera();
};

#endif // !MY_CAMERA_H

