#pragma once

#ifndef SKYBOX_H
#define SKYBOX_H

#include "../Object.h"

#include <stb/stb_image.h>

/**
 * @class Skybox
 *
 * @brief Class representing a skybox object (cubemap)
 */
class Skybox : public Object
{
public:
	/**
	* @brief Constructs a Skybox object.
	*
	* @param textureFolder path to folder conatining textures of the walls. Textures store each wall of cubemap in files with names px, nx, py, ny, pz, nz in png file format"
	*/
	Skybox(const char* textureFolder);	

	/**
	 * @brief Draws the Skybox object using the specified shader and camera.
	 * @param shader The shader used for rendering.
	 * @param camera The camera used for rendering.
	 */
	void draw(Shader& shader, Camera& camera);	
	
	/**
	 * @brief Function called on every update to update the Skybox object.
	 * @param ts The time since the last update.
	 */
	void onUpdate(Timestep timestep) {};

private:
	unsigned int skyboxVAO; ///< ID of skybox VAO 
	unsigned int skyboxVBO; ///< ID of skybox VBO 
	unsigned int skyboxEBO; ///< ID of skybox EBO 
	unsigned int cubemapTexture; /// <id of qubemap texture
	Shader* skyboxShader; ///< shader used for rendering skybox
};

#endif // !SKYBOX_H