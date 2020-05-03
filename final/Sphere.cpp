#if defined(__APPLE__)
#  include <OpenGL/gl3.h> // defines OpenGL 3.0+ functions
#else
#  if defined(WIN32)
#    define GLEW_STATIC 1
#  endif
#  include <GL/glew.h>
#endif

#include "Sphere.h"
#include "Util.h"

Sphere::Sphere(const glm::vec4& color = glm::vec4{ 1.f, 1.f, 1.f, 1.f }) : color{ color } {
	GenerateVexNormalIndices();
}


void Sphere::BuildArrays() {
	vertex_vao = new GLfloat[vertices.size() * 3];
	indices_vao = new GLuint[indices.size()];
	//normals_vao = new GLfloat[vertices.size() * 3];
	colors_vao = new GLfloat[vertices.size() * 4];

	for (int i = 0; i < vertices.size(); ++i) {
		vertex_vao[i * 3 + 0] = vertices[i].x;
		vertex_vao[i * 3 + 1] = vertices[i].y;
		vertex_vao[i * 3 + 2] = vertices[i].z;
		//normals_vao[i * 3 + 0] = vertices[i].x;
		//normals_vao[i * 3 + 1] = vertices[i].y;
		//normals_vao[i * 3 + 2] = vertices[i].z;
		colors_vao[i * 4 + 0] = color[0];
		colors_vao[i * 4 + 1] = color[1];
		colors_vao[i * 4 + 2] = color[2];
		colors_vao[i * 4 + 3] = color[3];
	}

	for (int i = 0; i < indices.size(); ++i)
		indices_vao[i] = indices[i];
}


void Sphere::BindVBO(unsigned int programID) {
	// Use a Vertex Array Object -- think of this as a single ID that sums up all the following VBOs
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Generate a buffer that will be sent to the video memory
	// For each ply object, it will get its own vertex buffer object, but it
	// would be much more efficient to put everything into one Vertex Buffer Object and send it over
	// only once to video memory. 

	// Note: If this seg faults, then Glee or Glew (however OpenGL 2.0 extensions are mangaged)
	// has not yet been initialized.
	//tell openGL to generate a new VBO object
	glGenBuffers(1, &vertexVBO_id);
	// Once we know how many buffers to generate, then hook up the buffer to the vertexVBO_id.
	glBindBuffer(GL_ARRAY_BUFFER, vertexVBO_id);
	// Now we finally copy data into the buffer object
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*vertices.size() * 3, vertex_vao, GL_STATIC_DRAW);


	//tell openGL to generate a new VBO object
	glGenBuffers(1, &indicesVBO_id);
	// Transfer the data from indices to a VBO indicesVBO_id
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesVBO_id);
	// Copy data into the buffer object. Note the keyword difference here -- GL_ELEMENT_ARRAY_BUFFER
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*indices.size(), indices_vao, GL_STATIC_DRAW);
	// Get the location of the attributes that enters in the vertex shader
	GLint position_attribute = glGetAttribLocation(programID, "myPosition");
	// Specify how the data for position can be accessed
	glVertexAttribPointer(position_attribute, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// Enable the attribute
	glEnableVertexAttribArray(position_attribute);


	////Repeat the process as building a vertexVBO, but this time for the normals
	//glGenBuffers(1, &normalVBO_id);
	//// bind the newly generated buffer to the normalVBO_id.
	//glBindBuffer(GL_ARRAY_BUFFER, normalVBO_id);
	//// Now we finally copy data into the buffer object
	//glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*vertices.size() * 3, normals_vao, GL_STATIC_DRAW);
	//// Get the location of the attributes that enters in the vertex shader
	//GLint normal_attribute = glGetAttribLocation(programID, "myNormal");
	//// Specify how the data for position can be accessed
	//glVertexAttribPointer(normal_attribute, 3, GL_FLOAT, GL_TRUE, 0, 0);
	//// Enable the attribute
	//glEnableVertexAttribArray(normal_attribute);


	// color
	glGenBuffers(1, &colorVBO_id);
	glBindBuffer(GL_ARRAY_BUFFER, colorVBO_id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*vertices.size() *4, colors_vao, GL_STATIC_DRAW);
	GLint color_attribute = glGetAttribLocation(programID, "myColor");
	glVertexAttribPointer(color_attribute, 4, GL_FLOAT, GL_TRUE, 0, 0);
	glEnableVertexAttribArray(color_attribute);
}

void Sphere::RenderVBO() {
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLE_STRIP, indices.size(), GL_UNSIGNED_INT, 0);
}


// https://github.com/Rainfalllen/RenderToy/blob/1d5b167a6121b56b1113a9773db1db59a18776cd/Primitive/Sphere.h#L60

void Sphere::GenerateVexNormalIndices() {
	// generate vertices and normals
	float dx = 2 * PI / SEGMENT_X;
	float dy = PI / SEGMENT_Y;

	for (int j = 0; j <= SEGMENT_Y; ++j)
		for (int i = 0; i <= SEGMENT_X; ++i)
			vertices.push_back(glm::vec3{ cosf(i * dx) * sinf(j * dy), cosf(j * dy), sinf(i * dx) * sinf(j * dy) });

	// generate indices
	bool isOddRow = false;
	for (int j = 0; j < SEGMENT_Y; ++j) {
		if (!isOddRow) {
			for (int i = 0; i <= SEGMENT_X; ++i) {
				indices.push_back(j * (SEGMENT_X + 1) + i);
				indices.push_back((j + 1) * (SEGMENT_X + 1) + i);
			}
		}
		else {
			for (int i = SEGMENT_X; i >= 0; --i) {
				indices.push_back((j + 1) * (SEGMENT_X + 1) + i);
				indices.push_back(j * (SEGMENT_X + 1) + i);
			}
		}
		isOddRow = !isOddRow;
	}
}

