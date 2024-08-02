#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include <glad/glad.h>

#include "VBO.h"

/**
* @class VAO
*
* @brief Class abstracting the OpenGL Vertex Array Object
*/
class VAO
{
public:
	GLuint ID; ///< VAO ID

	/**
	* @brief VAO class constructor
	*/
	VAO();

	/**
	* @brief links VBO data as attributes of VAO
	*
	* @param vbo Reference to vertex buffer which is the source of data
	* @param layout number of layout where data can be accessed form shader
	* @param numOfComponents number of items that are going to be linked to VAO
	* @param type type of components that are being linked
	* @param stride distance between each item to be linked
	* @param offset pointer representing the distance to first item to be linked
	*/
	void linkAttrib(VBO& vbo, GLuint layout, GLuint numOfComponents, GLenum type, GLsizeiptr stride, void* offset);
	
	/**
	* @brief binds VAO object
	*/
	void vaoBind();

	/**
	* @brief unbinds VAO object
	*/
	void vaoUnbind();

	/**
	* @brief deletes VAO object
	*/
	void vaoDelete();
};

#endif // !VAO_CLASS_H