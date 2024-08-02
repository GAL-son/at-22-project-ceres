#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

/**
* @brief reads a file
*
* @param filename path to file to be read
* @return file contents in a string
*/
std::string getFileContents(const char* filename);

/**
 * @class Shader
 *
 * @brief Class representing a OpenGL shader program
 */
class Shader
{
public:
	GLuint ID; ///< ID of shader object

	/**
	 * @brief Constructor for Enemy.
	 * 
	 * @param vertexFile path to file containing vertex sahder code
	 * @param fragmentFile path to file containing fragment sahder code
	 */
	Shader(const char* vertexFile, const char* fragmentFile);

	/**
	 * @brief activates the shader
	 */
	void activate();

	/**
	 * @brief deletes the shader
	 */
	void deleteShader();

private:
	/**
	 * @brief checks if shader was compiled correctly
	 * 
	 * @param shader id of comiled shader
	 * @param type type of compiled shader (ex. vertex, fragment)
	 */
	void static compileErrors(unsigned int shader, const char* type);
};

#endif // !SHADER_CLASS_H
