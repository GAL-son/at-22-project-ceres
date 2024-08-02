#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include <glad/glad.h>
#include <vector>


/**
* @class EBO
* 
* @brief Class abstracting the OpenGL Element Buffer Object
*/
class EBO
{
public:
	GLuint ID; ///< EBO ID

	/**
	* @brief EBO class constructor
	* 
	* @param indices vector of indecies
	*/
	EBO(std::vector<GLuint> indices);

	/**
	* @brief binds EBO object
	*/
	void eboBind();

	/**
	* @brief unbinds EBO object
	*/
	void eboUnbind();

	/**
	* @brief deletes EBO object
	*/
	void eboDelete();
};

#endif // !EBO_CLASS_H
