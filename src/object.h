
#ifndef OBJECT_H_
#define OBJECT_H_

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ships.h"

struct vertice {
		GLfloat coord[3];
		GLfloat texcoord[2];
		GLfloat normal[3];
		GLfloat colour[3];
	};

struct face {
	GLushort vIndex[3];
	GLushort texIndex[3];
	GLushort normIndex[3];
};

class ObjectModel {
protected:
	float m_x, m_y, m_z;
	float phi, theta, yaw;
	float scale;

public:
	ObjectModel();
	glm::mat4 GetTransform();
};

/**
 * This is the base view class used to create all 3D objects in the game.
 */
class ObjectView {
private:
	GLint m_M;
	GLint m_M_inv;
	GLuint vao, vbo_vertices;
	std::vector<glm::vec3> m_vertices;
	std::vector<glm::vec2> m_texcords;
	std::vector<glm::vec3> m_normals;

	std::vector<face> m_faces;
	std::vector<vertice> m_buffer;

protected:
	int LoadObject(const char* filename);
	void SetM(glm::mat4 M);

public:
	ObjectView();
	virtual ~ObjectView();

	/** Upload data to the graphics card. */
	int Upload();

	/** Render an object */
	//void RenderObject();

	void Render(ObjectModel*);
};

#endif /* OBJECT_H_ */
