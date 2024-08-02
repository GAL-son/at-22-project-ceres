#include "Light.h"

void Light::passToShader(Shader& shader, Camera& camera, GLuint index)
{
	shader.activate();
	glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.position.x, camera.position.y, camera.position.z);

	std::string uniform = "lights[" + std::to_string(index) + "].";

	GLuint location = 0;
	
	//Send Type
	location = glGetUniformLocation(shader.ID, (uniform + "Type").c_str());
	//std::cout << (uniform + "Type").c_str() << ": " << this->type << std::endl;
	glUniform1i(location, this->type);

	//Send Position
	location = glGetUniformLocation(shader.ID, (uniform + "Position").c_str());
	glUniform3f(location, this->position.x, this->position.y, this->position.z);
	
	//Send Color
	location = glGetUniformLocation(shader.ID, (uniform + "Color").c_str());
	glUniform3f(location, this->color.x, this->color.y, this->color.z);
	
	//Send Direction
	location = glGetUniformLocation(shader.ID, (uniform + "Direction").c_str());
	glUniform3f(location, this->direction.x, this->direction.y, this->direction.z);

	//Send Intensity
	location = glGetUniformLocation(shader.ID, (uniform + "Intensity").c_str());
	glUniform1f(location, this->intensity);

}
