/*
 * views.cpp
 *
 *  Created on: 15 Jan 2014
 *      Author: sam
 */

#include "shipviews.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <glm/glm.hpp>

#include <math.h>

ShipsView::ShipsView() :
m_surface(0), m_screenflags(0), m_fullscreen(1) {
	this->m_fullscreen? this->m_width=1600: this->m_width = 800;
	this->m_fullscreen? this->m_height=900: this->m_height = 600;
}

ShipsView::~ShipsView() {
	this->m_surface = SDL_SetVideoMode(0,0,0, this->m_screenflags);
	if(this->m_surface)
		SDL_FreeSurface(this->m_surface);

}

int ShipsView::CreateView() {

	// Initialise SDL
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
		return 1;

	// If it hasn't already been created (it shouldn't have), create a new window.
	if(!this->m_surface)
		this->m_surface = SDL_SetVideoMode(m_width,m_height, 32,
				SDL_HWSURFACE | SDL_GL_DOUBLEBUFFER | SDL_OPENGL);

	// If this function fails, then we can't continue; return a fail code.
	if(!this->m_surface) return 1;

	this->m_screenflags = this->m_surface->flags;

	if(this->m_fullscreen)
		this->m_surface = SDL_SetVideoMode(0,0,0, this->m_screenflags | SDL_FULLSCREEN);

	SDL_ShowCursor(0);

	//glClearColor(192.0f/255.0f, 0, 0, 1.0f);
	glClearColor(0.f/255.0f, 0, 0, 1.0f);
	glClearDepth(1.0f);

	// Viewport set
	glViewport(0, 0, m_width, m_height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0, m_width, 0, m_height , 1000, -1000);

	glMatrixMode(GL_MODELVIEW);
	//glMatrixMode(GL_PROJECTION);

	glShadeModel(GL_SMOOTH);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LINE_SMOOTH);
	glEnable( GL_POLYGON_SMOOTH );
	//glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );
	//glHint( GL_POLYGON_SMOOTH_HINT, GL_NICEST );
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glDisable(GL_DEPTH_TEST);

	glLoadIdentity();

	// Set the window's title.
	SDL_WM_SetCaption("Ships <alpha> - Sam Berry",0);



	// Return OK
	return 0;
}

void ShipsView::Loop(double dt) {

}

void ShipsView::Render() {

}

int ShipsView::GetWidth() {
	return this->m_width;
}

int ShipsView::GetHeight() {
	return this->m_height;
}
