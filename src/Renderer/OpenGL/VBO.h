#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

/**
 * @struct Vertex
 * 
 * @brief structure describing vertex
 */
struct Vertex
{
	glm::vec3 position; ///< vertex position
	glm::vec3 normal; ///< vertex normal
	glm::vec3 color; ///< vertex color
	glm::vec2 texUV; ///< vertex texture coordinate
};

/**
* @class VBO
*
* @brief Class abstracting the OpenGL Vertex Buffer Object
*/
class VBO
{
public:
	GLuint ID; ///< VBO ID

	/**
	* @brief EBO class constructor
	*
	* @param indices vector of Vercices
	*/
	VBO(std::vector<Vertex> verices);

	/**
	* @brief binds VBO object
	*/
	void vboBind();

	/**
	* @brief unbinds VBO object
	*/
	void vboUnbind();

	/**
	* @brief deletes VBO object
	*/
	void vboDelete();
};

#endif // !VBO_CLASS_H
