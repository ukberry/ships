/*
 * shipviews.h
 *
 *  Created on: 30 Jan 2014
 *      Author: sam
 */

#ifndef SHIPVIEWS_H_
#define SHIPVIEWS_H_

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "gamecontroller.h"

class Ship;

class ShipsView {
private:
	SDL_Surface *m_surface;
	int m_screenflags;
	bool m_fullscreen;
	int m_width;
	int m_height;

	GLint m_program;

public:
	ShipsView();
	~ShipsView();

	int CreateView();

	int GetWidth();
	int GetHeight();
	GLuint GetGraphicsProg();
};

/**
 * This is the base view class used to create all 3D objects in the game.
 */
class ObjectView {
private:
	GLuint vbo_vertices, ibo_faces;
	std::vector<glm::vec3> m_vertices;
	std::vector<GLushort> m_faces;
public:
	ObjectView();
	~ObjectView();

	/** Upload data to the graphics card. */
	int Upload();

	/** Send the instructions to draw the object. */
	void Render();
};

class ShipView : public ObjectView {
private:
public:
	ShipView();
	~ShipView();
};

/**
 * This class is responsible for managing the renderable objects in the game.
 */
class GameView {
private:
	std::vector<ObjectView*> m_objectviews;

};


#endif /* SHIPVIEWS_H_ */
