#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include <glad/glad.h>
#include <stb/stb_image.h>

#include "Shader.h"

/**
 * @enum TextureType
 *
 * @brief Enumeration representing different types of textures
 */
enum TextureType {
	TEXTURE_DIFFUSE,
	TEXTURE_SPECULAR,
};

/**
 * @class Texture
 *
 * @brief Class representing a OpenGL Texture
 */
class Texture
{
public:
	GLuint ID; ///< Texture ID
	TextureType type; ///< Texture type
	GLuint unit; ///< Texture unit, used to differentaite textures between each other

	/**
	* @brief Constructs a Texture object.
	*
	* @param imagePath specifies path to texture image file
	* @param texType specifies type of texture
	* @param unit specifies textuew uniform id
	*/
	Texture(const char* imagePath, TextureType texType, GLuint unit);

	/**
	* @brief Sends texture uniform to shader
	*
	* @param shader specifies path to texture image file
	* @param uniform specifies type of texture
	* @param unit specifies texture unit
	*/
	void texUnit(Shader& shader, const char* uniform, GLuint unit);

	/**
	* @brief binds texture
	*/
	void textureBind();

	/**
	* @brief unbinds texture
	*/
	void textureUnbind();

	/**
	* @brief deletes texture
	*/
	void textureDelete();

	/**
	* @brief gets type of texture
	* 
	* @return string representation of texture type
	*/
	std::string getTypeString();
};

#endif // !TEXTURE_CLASS_H
