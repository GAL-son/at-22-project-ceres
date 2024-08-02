#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include <string>

#include "VAO.h"
#include "EBO.h"
#include "Texture.h"
#include "../Camera.h"

/**
 * @class Mesh
 *
 * @brief Class representing a Mesh - a colection of vertices and corresponding indices and textures
 */
class Mesh
{
public:
	std::vector <Vertex> vertices; ///< vector of vertices of a mesh
	std::vector <GLuint> indices; ///< vector of indices of a mesh
	std::vector <Texture> textures; ///< vector of textures of a mesh

	VAO vao; ///< VAO object of a mesh

	/**
	* @brief constructs the mesh object
	*
	* @param vertices vector of vertices to be assigned to mesh
	* @param indices vector of indices to be assigned to mesh
	* @param texures vector of texures to be assigned to mesh
	*/
	Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture>& texures);

	/**
	 * @brief Draws Mesh using the specified shader and camera, with given position, rotation and scale
	 * 
	 * @param shader The shader used for rendering.
	 * @param camera The camera used for rendering
	 * @param model model matrix - used when Mesh is in a bigger colection of meshec (eg. Model) (default = glm::mat4(1.0) //Unity matrix - no effect)
	 * @param translation translation of Mesh (default = glm::vec3(0.0f, 0.0f, 0.0f), //no effect)
	 * @param rotation rotation of Mesh in form of quatermion (default = glm::quat(1.0f, 0.0f, 0.0f, 0.0f), //no effect)
	 * @param scale scale of mesh (default = glm::vec3(0.0f, 0.0f, 0.0f), //no effect)
	 */
	void draw
	(
		Shader& shader,
		Camera& camera,
		glm::mat4 model = glm::mat4(1.0f),
		glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f),
		glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
		glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f)
	);	
};

#endif // !MESH_CLASS_H
