#include "ships.h"
#include "shipsviews.h"


ObjectView::ObjectView() : vbo_vertices(0), ibo_faces(0) {
	this->m_vertices.push_back(glm::vec3(-100.,-70.,0.));
	this->m_vertices.push_back(glm::vec3(100.,-70.,0.));
	this->m_vertices.push_back(glm::vec3(0.,70.,0.));

	this->m_faces.push_back(0);
	this->m_faces.push_back(1);
	this->m_faces.push_back(2);

}

ObjectView::~ObjectView() {
	if(vbo_vertices) 	glDeleteBuffers(1, &vbo_vertices);
	if(ibo_faces)		glDeleteBuffers(1, &ibo_faces);
}

int ObjectView::Upload() {

	if(this->m_vertices.size()) {
		glGenBuffers(1, &this->vbo_vertices);
		std::cout << "Uploading vertices...\n";
	}

	return 0;
}

void ObjectView::Render() {

}

ShipView::ShipView() {

}


ShipView::~ShipView() {

}

