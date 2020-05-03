#ifndef SPHERE_H
#define SPHERE_H

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>


class Sphere {
public:
	Sphere(const glm::vec4& color);

	void BuildArrays();
	void BindVBO(unsigned int programID);
	void RenderVBO();

private:
	void GenerateVexNormalIndices();

public:
	GLuint vao;

private:
	glm::vec4 color;
	std::vector<glm::vec3> vertices;
	std::vector<int> indices;

	// Id for Vertex Buffer Object
	GLuint vertexVBO_id, indicesVBO_id, normalVBO_id, colorVBO_id;
	// Special arrays that are used for vertex buffer objects
	GLfloat* vertex_vao;
	GLuint* indices_vao;
	//GLfloat* normals_vao;
	GLfloat* colors_vao;
};


#endif