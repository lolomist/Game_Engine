#pragma once

#include "Vertex.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

#include <glm/glm.hpp>

static void loadOBJ(const char* file_name, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices, glm::vec3 color)
{
	//vertex portions
	std::vector<glm::fvec3> vertex_positions;
	std::vector<glm::fvec2> vertex_texcoords;
	std::vector<glm::fvec3> vertex_normals;

	//Face (Indices) vectors
	std::vector<uint32_t> vertex_position_indicies;
	std::vector<uint32_t> vertex_texcoord_indicies;
	std::vector<uint32_t> vertex_normal_indicies;

	std::stringstream ss;
	std::ifstream in_file(file_name);
	std::string line = "";
	std::string prefix = "";
	glm::vec3 temp_vec3;
	glm::vec2 temp_vec2;
	uint32_t temp_uint = 0;
	int total_indices = 0;

	if (!in_file.is_open()) {
		throw std::runtime_error("OBJ LOADER : Could not open file");
	}

	while (std::getline(in_file, line)) {

		// GET the prefix of the line
		ss.clear();
		ss.str(line);
		ss >> prefix;

		if (prefix == "v") { //Vertex position
			ss >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z;
			vertex_positions.push_back(temp_vec3);
		}
		else if (prefix == "vt") { //Textures coordinates
			ss >> temp_vec2.x >> temp_vec2.y;
			temp_vec2.y = 1.0f - temp_vec2.y;
			vertex_texcoords.push_back(temp_vec2);
		}
		else if (prefix == "vn") { //Vertex normals
			ss >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z;
			vertex_normals.push_back(temp_vec3);
		}
		else if (prefix == "f") {
			int counter = 0;

			//tmp vectors for storing each indices of this face
			std::vector<uint32_t> temp_vertex_position_indicies;
			std::vector<uint32_t> temp_vertex_texcoord_indicies;
			std::vector<uint32_t> temp_vertex_normal_indicies;

			while (ss >> temp_uint)
			{
				//Pushing indices into correct arrays
				if (counter == 0) {
					temp_vertex_position_indicies.push_back(temp_uint);
				}
				else if (counter == 1) {
					temp_vertex_texcoord_indicies.push_back(temp_uint);
				}
				else if (counter == 2) {
					temp_vertex_normal_indicies.push_back(temp_uint);
				}

				//Handling characters
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

				// Reset counter
				if (counter > 2) {
					counter = 0;
				}
			}

			if (temp_vertex_position_indicies.size() == 4) {
				vertex_position_indicies.push_back(temp_vertex_position_indicies[0]);
				vertex_position_indicies.push_back(temp_vertex_position_indicies[1]);
				vertex_position_indicies.push_back(temp_vertex_position_indicies[2]);
				vertex_position_indicies.push_back(temp_vertex_position_indicies[0]);
				vertex_position_indicies.push_back(temp_vertex_position_indicies[2]);
				vertex_position_indicies.push_back(temp_vertex_position_indicies[3]);

				vertex_texcoord_indicies.push_back(temp_vertex_texcoord_indicies[0]);
				vertex_texcoord_indicies.push_back(temp_vertex_texcoord_indicies[1]);
				vertex_texcoord_indicies.push_back(temp_vertex_texcoord_indicies[2]);
				vertex_texcoord_indicies.push_back(temp_vertex_texcoord_indicies[0]);
				vertex_texcoord_indicies.push_back(temp_vertex_texcoord_indicies[2]);
				vertex_texcoord_indicies.push_back(temp_vertex_texcoord_indicies[3]);

				vertex_normal_indicies.push_back(temp_vertex_normal_indicies[0]);
				vertex_normal_indicies.push_back(temp_vertex_normal_indicies[1]);
				vertex_normal_indicies.push_back(temp_vertex_normal_indicies[2]);
				vertex_normal_indicies.push_back(temp_vertex_normal_indicies[0]);
				vertex_normal_indicies.push_back(temp_vertex_normal_indicies[2]);
				vertex_normal_indicies.push_back(temp_vertex_normal_indicies[3]);
			}
			else if (temp_vertex_position_indicies.size() == 3) {
				vertex_position_indicies.push_back(temp_vertex_position_indicies[0]);
				vertex_position_indicies.push_back(temp_vertex_position_indicies[1]);
				vertex_position_indicies.push_back(temp_vertex_position_indicies[2]);

				vertex_texcoord_indicies.push_back(temp_vertex_texcoord_indicies[0]);
				vertex_texcoord_indicies.push_back(temp_vertex_texcoord_indicies[1]);
				vertex_texcoord_indicies.push_back(temp_vertex_texcoord_indicies[2]);

				vertex_normal_indicies.push_back(temp_vertex_normal_indicies[0]);
				vertex_normal_indicies.push_back(temp_vertex_normal_indicies[1]);
				vertex_normal_indicies.push_back(temp_vertex_normal_indicies[2]);
			}
			else {
				throw std::runtime_error("unsupported 3D object :(");
			}
		}
	}

	//Build final vertex array (mesh)
	for (size_t i = 0; i < vertex_position_indicies.size(); ++i) {
		Vertex vertex{};

		//std::cout << "index : " << vertex_position_indicies[i] - 1<< std::endl;
		/*std::cout << "indicies x: " << vertex_positions[vertex_position_indicies[i]].x << std::endl;
		std::cout << "indicies y: " << vertex_positions[vertex_position_indicies[i]].y << std::endl;
		std::cout << "indicies z: " << vertex_positions[vertex_position_indicies[i]].z << std::endl;*/

		vertex.pos = vertex_positions[vertex_position_indicies[i] - 1];
		vertex.texCoord = vertex_texcoords[vertex_texcoord_indicies[i] - 1];
		vertex.color = color;
		vertex.normal = vertex_normals[vertex_normal_indicies[i] - 1];

		/*std::cout << "vertex[" << i << "] X : " <<  vertex.pos.x <<std::endl;
		std::cout << "vertex[" << i << "] Y : " << vertex.pos.y << std::endl;
		std::cout << "vertex[" << i << "] Z : " << vertex.pos.z << std::endl;*/

		vertices.push_back(vertex);
		indices.push_back((uint32_t)indices.size());
	}
}