#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

#include <glm/glm.hpp>
#include "Mesh.h"

static Mesh& getVetriciesFromOBJ(const char* path)
{
	//Load Vertices
	std::vector<glm::vec3> vertexPositions;
	std::vector<glm::vec3> vertexNormals;
	std::vector<glm::vec2> vertexUVtex;

	//load Indeces
	std::vector<GLuint> vertexPositionIndecies;
	std::vector<GLuint> vertexNormalIndecies;
	std::vector<GLuint> vertexUVTexIndecies;

	//Vertex Array
	std::vector<Vertex> vertices;
	std::vector<GLuint> indeces;
	std::vector<Texture> textures;
	std::string texturePath = "path";

	std::stringstream ss;
	std::ifstream inFile(path);
	std::string line = "";
	std::string prefix = "";

	glm::vec3 tempVec3;
	glm::vec3 tempVec2;
	GLuint tempGLuint = 0;


	if (!inFile.is_open())
	{
		throw "ERROR OBJ LOADER COULD NOT OPEN FILE";
	}

	while (std::getline(inFile, line))
	{
		//get the line prefix
		ss.str(line);
		ss >> prefix;

		std::cout << prefix;

		if (prefix == "#")
		{

		}
		else if (prefix == "o")
		{

		}
		else if (prefix == "s") {}
		else if (prefix == "use_mtl") {}
		else if (prefix == "v") // VERTRX POSITION
		{
			ss >> tempVec3.x >> tempVec3.y >> tempVec3.z;
			vertexPositions.push_back(tempVec3);
		}
		else if (prefix == "vt") // TEXTURE COORDINATE
		{
			ss >> tempVec2.x >> tempVec2.y;
			vertexPositions.push_back(tempVec2);
		}
		else if (prefix == "vn") // VERTRX NORMAL
		{
			ss >> tempVec3.x >> tempVec3.y >> tempVec3.z;
			vertexNormals.push_back(tempVec3);
		}
		else if (prefix == "f")
		{
			int counter = 0;
			while (ss >> tempGLuint)
			{
				if (counter == 0)
				{
					vertexPositionIndecies.push_back(tempGLuint);
					indeces.push_back(tempGLuint);
				}
				else if (counter == 1)
					vertexUVTexIndecies.push_back(tempGLuint);
				else if (counter == 2)
					vertexNormalIndecies.push_back(tempGLuint);

				if (ss.peek() == '/')
				{
					++counter;
					ss.ignore(1, '/');
				}
				else if (ss.peek() == ' ')
				{
					++counter;
					ss.ignore(1, ' ');
				}

				if (counter > 2)
					counter = 0;
			}
		}
		else if (prefix == "t")
		{
			std::string temp = "";
			ss >> temp;			
			texturePath += temp;
			Texture tex(texturePath.c_str(), TEXTURE_DIFFUSE, 0);
			textures.push_back(tex);
			texturePath = path;
		}
		else {}

		//debug
		//std::cout << line << std::endl;
	}
	// Build final VertexArray
	vertices.resize(vertexPositionIndecies.size(), Vertex());
	std::cout << vertexPositionIndecies.size();

	for (size_t i = 0; i < vertices.size(); i++)
	{
		vertices[i].position = vertexPositions[vertexPositionIndecies[i]];
		vertices[i].normal = vertexNormals[vertexNormalIndecies[i]];
		vertices[i].texUV = vertexUVtex[vertexUVTexIndecies[i]];
		vertices[i].color = glm::vec3(1.0, 1.0, 1.0);
	}

	
	Mesh m(vertices, indeces, textures);
	return m;
}


