/*
 * object.cpp
 *
 *  Created on: 1 Jul 2014
 *      Author: sam
 */

#include "object.h"

#include <string>
#include <fstream>
#include <sstream>

enum Vertice_attributes {
	va_coord, va_texCoord, va_normal, va_colour
};

face ParseObjLine(std::string input) {

	using namespace std;

	face theFace( { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } });

	istringstream stream(input);

	char next;
	int index = 0;
	int block = 0;
	bool numeric_prev = false;

	while (stream.tellg() >= 0) {

		stream >> next;

		switch (next) {
		case '/':
			index++;
			numeric_prev = false;
			break;
		default:
			if (!isdigit(next)) {
				// The default should be numeric. If it isn't, the file is not
				// well-formed!
				cerr << "Whoops - expected an index to vertice attribute!\n";
				return theFace;
			}
			if (numeric_prev) {
				/*
				 * If the previous value was numeric, then we haven't seen a
				 * separator, it would've been a space. So we have moved to the
				 * next block; set the index to zero and increment the block
				 * index.
				 */
				block++;
				index = 0;
			}

			// Set the pointer back one unit and read number into the struct.
			stream.seekg(-1, ios_base::cur);

			// index - whether the value is a vCoord, vTexCoord, or vNormal
			// block - the x, y, or z coefficient.

			/*
			 * Since the struct is a structure with 9 unsigned shorts, reference
			 * by address.
			 */
			stream >> *((unsigned short*) &theFace + index * 3 + block);
			numeric_prev = true;
		}
	}

	for (int i = 0; i < 3; i++) {
		theFace.vIndex[i]--;
		theFace.texIndex[i]--;
		theFace.normIndex[i]--;
	}

	return theFace;
}

ObjectView::ObjectView() :
		vao(0), vbo_vertices(0) {

// Create a reference to the Model transform matrix.
	this->m_M = ShipsController::GetInstance()->GetView()->GetM();
	this->m_M_inv = ShipsController::GetInstance()->GetView()->GetM_inv();

	this->m_vertices.push_back(glm::vec3(-0.1, -0.07, 0.2));
	this->m_vertices.push_back(glm::vec3(0.1, -0.07, 0.2));
	this->m_vertices.push_back(glm::vec3(0., 0.07, 0.2));
	this->m_vertices.push_back(glm::vec3(0., 0., 0.));

	//face a_face = { 0, 1, 2 };
	//this->m_faces.push_back(a_face);
	//this->m_faces.push_back(face( { 1, 2, 3 }));
	//this->m_faces.push_back(face( { 0, 1, 3 }));
	//this->m_faces.push_back(face( { 0, 2, 3 }));

	std::cout << "ObjectView constructor finished!\n";

}

ObjectView::~ObjectView() {
	if (vao)
		glDeleteVertexArrays(1, &vao);
	if (vbo_vertices)
		glDeleteBuffers(1, &vbo_vertices);
}

int ObjectView::Upload() {

	std::vector<face>::iterator it;
	vertice temp;

	for (it = m_faces.begin(); it != m_faces.end(); it++) {
		face curr = *it;

		for (int i = 0; i < 3; i++) {
			temp.coord[0] = this->m_vertices[curr.vIndex[i]].x;
			temp.coord[1] = this->m_vertices[curr.vIndex[i]].y;
			temp.coord[2] = this->m_vertices[curr.vIndex[i]].z;

			if (curr.texIndex[i] != 65535) {
				temp.texcoord[0] = this->m_texcords[curr.texIndex[i]].x;
				temp.texcoord[1] = this->m_texcords[curr.texIndex[i]].y;
			}

			if (curr.normIndex[i] != 65535) {

				temp.normal[0] = this->m_normals[curr.normIndex[i]].x;
				temp.normal[1] = this->m_normals[curr.normIndex[i]].y;
				temp.normal[2] = this->m_normals[curr.normIndex[i]].z;

				std::cout << "Normal vector found!: " << temp.normal[0] << ", "
						<< temp.normal[1] << ", " << temp.normal[2] << "\n";
			} else {
				temp.normal[0] = temp.normal[1] = temp.normal[2] = 0;
			}

			temp.colour[0] = 1.;
			temp.colour[1] = 1.;
			temp.colour[2] = 1.;

			this->m_buffer.push_back(temp);
			std::cout << "Iteration " << i << ": " << curr.vIndex[i] << "\n";
		}
	}

	if (this->m_buffer.size()) {
		std::cout << "Uploading vertices...\n";

		glGenVertexArrays(1, &this->vao);
		glGenBuffers(1, &this->vbo_vertices);

		glBindVertexArray(this->vao);
		glBindBuffer(GL_ARRAY_BUFFER, this->vbo_vertices);
		glBufferData(GL_ARRAY_BUFFER, m_buffer.size() * sizeof(m_buffer[0]),
				m_buffer.data(), GL_STATIC_DRAW);

		glVertexAttribPointer(va_coord, 3, GL_FLOAT, GL_FALSE,
				sizeof(struct vertice),
				(GLvoid*) offsetof(struct vertice, coord));
		glVertexAttribPointer(va_texCoord, 2, GL_FLOAT, GL_FALSE,
				sizeof(struct vertice),
				(GLvoid*) offsetof(struct vertice, texcoord));
		glVertexAttribPointer(va_normal, 3, GL_FLOAT, GL_FALSE,
				sizeof(struct vertice),
				(GLvoid*) offsetof(struct vertice, normal));
		glVertexAttribPointer(va_colour, 3, GL_FLOAT, GL_FALSE,
				sizeof(struct vertice),
				(GLvoid*) offsetof(struct vertice, colour));

		glEnableVertexAttribArray(va_coord);
		glEnableVertexAttribArray(va_texCoord);
		glEnableVertexAttribArray(va_normal);
		glEnableVertexAttribArray(va_colour);

		// All data should now be on the graphics card... free it from computer memory.
		//this->m_buffer.clear();
	}

	std::cout << "Vertices uploaded!\n";
	return 0;
}

int ObjectView::LoadObject(const char* filename) {

	/*TODO(sam)- Create a more elegant storage for shipper objects!
	 * Current method is not acceptable!
	 */

	std::string data_location(TOPDIR);
	data_location += "/data/";
	data_location += filename;
	std::ifstream file(data_location.c_str(), std::ios::in);

	data_location = DATADIR;
	data_location += "/ships/objects/";
	data_location += filename;

	std::cout << "Trying location: " << data_location << "\n";

	if(!file) file.open(data_location.c_str(), std::ios::in);

	if (!file) {
		std::cerr << "Cannot load object file " << filename << ".\n";
		return 1;
	}

	this->m_vertices.clear();
	std::cout << "vertices during loadObject = " << m_vertices.size() << "\n";
	this->m_faces.clear();

	std::string line;
	while (getline(file, line)) {
		if (line.substr(0, 2) == "v ") {
			std::istringstream s(line.substr(2));
			glm::vec3 v;
			s >> v.x;
			s >> v.y;
			s >> v.z;
			this->m_vertices.push_back(v);

//			std::cout << "Vertice added V = " << v.x << "," << v.y << ", " << v.z << "\n";
		} else if (line.substr(0, 2) == "f ") {
			// Okay, this line is a little more complicated...
			face A = ParseObjLine(line.substr(2));
			this->m_faces.push_back(A);

		} else if (line.substr(0, 2) == "vt") {
			std::istringstream s(line.substr(3));
			glm::vec2 vt;
			s >> vt.x;
			s >> vt.y;
			this->m_texcords.push_back(vt);

		} else if (line.substr(0, 2) == "vn") {
			std::istringstream s(line.substr(3));
			glm::vec3 vn;
			s >> vn.x;
			s >> vn.y;
			s >> vn.z;
			this->m_normals.push_back(vn);

		} else {
			// IGNORE!
		}
	}

	return 0;
}

void ObjectView::SetM(glm::mat4 M) {
	glUniformMatrix4fv(this->m_M, 1, GL_FALSE, glm::value_ptr(M));

	glm::mat3 M_invT = glm::transpose(glm::inverse(glm::mat3(M)));
	glUniformMatrix3fv(this->m_M_inv, 1, GL_FALSE, glm::value_ptr(M_invT));

	//glUniform1f(ShipsController::GetInstance()->GetView()->GetisSprite(),1);
}

void ObjectView::Render(ObjectModel* model) {
	glBindVertexArray(this->vao);

	this->SetM(model->GetTransform());
	glDrawArrays(GL_TRIANGLES, 0, m_buffer.size());
}

ObjectModel::ObjectModel() :
		phi(0), theta(0), yaw(0), scale(1) {

}

glm::mat4 ObjectModel::GetTransform() {
	glm::mat4 M = glm::translate(glm::mat4(1), glm::vec3(m_x, m_y, m_z));
	M = glm::rotate(M, this->phi, glm::vec3(0, 0, 1));
	M = glm::rotate(M, this->theta, glm::vec3(1, 0, 0));
	M = glm::rotate(M, this->yaw, glm::vec3(0, 1, 0));
	M = glm::scale(M, glm::vec3(scale));

	return M;
}
