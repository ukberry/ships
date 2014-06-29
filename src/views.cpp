/*
 * views.cpp
 *
 *  Created on: 15 Jan 2014
 *      Author: sam
 */

#include "shipsviews.h"

#include "shaders.h"

#include <math.h>

ShipsView::ShipsView() :
		m_surface(0), m_screenflags(0), m_fullscreen(0), m_program(0) {
	this->m_fullscreen ? this->m_width = 1920 : this->m_width = 1024;
	this->m_fullscreen ? this->m_height = 1080 : this->m_height = 768;
}

ShipsView::~ShipsView() {

	this->m_surface = SDL_SetVideoMode(0, 0, 0, this->m_screenflags);
	if (this->m_surface)
		SDL_FreeSurface(this->m_surface);

	if (m_program) {
		glDeleteProgram(m_program);
		std::cout << "OpenGL program freed from graphics card.\n";
	}

}

int ShipsView::CreateView() {

	// Initialise SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		return 1;

	// If it hasn't already been created (it shouldn't have), create a new window.
	if (!this->m_surface)
		this->m_surface = SDL_SetVideoMode(m_width, m_height, 32,
		SDL_HWSURFACE | SDL_GL_DOUBLEBUFFER | SDL_OPENGL);

	// If this function fails, then we can't continue; return a fail code.
	if (!this->m_surface)
		return 1;

	this->m_screenflags = this->m_surface->flags;

	if (this->m_fullscreen)
		this->m_surface = SDL_SetVideoMode(0, 0, 0,
				this->m_screenflags | SDL_FULLSCREEN);

	SDL_ShowCursor(0);

	/* Extension wrangler initialising */
	GLenum glew_status = glewInit();
	if (glew_status != GLEW_OK) {
		std::cerr << "Error: " << glewGetErrorString(glew_status) << "\n";
		return EXIT_FAILURE;
	}

	m_program = create_program();

	if(!m_program) {
		std::cerr << "Error: Failed to compile shaders on the graphics card\n";
		return EXIT_FAILURE;
	}

	//glClearColor(192.0f/255.0f, 0, 0, 1.0f);
	glClearColor(1., 1., 1., 1.0f);
	glClearDepth(1.0f);

	glEnable(GL_DEPTH_TEST);

	glEnable (GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_DONT_CARE);

	glLineWidth(1.5f);

	// Set the window's title.
	SDL_WM_SetCaption("Ships <alpha> - Sam Berry", 0);

	// Return OK
	return 0;
}

int ShipsView::GetWidth() {
	return this->m_width;
}

int ShipsView::GetHeight() {
	return this->m_height;
}

GLuint ShipsView::GetGraphicsProg() {
	return this->m_program;
}

