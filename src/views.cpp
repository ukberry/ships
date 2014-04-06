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
m_surface(0), m_rot(0), o_rot(0), m_screenflags(0), obj(0), m_fullscreen(1) {
	this->m_fullscreen? this->m_width=1920: this->m_width = 1200;
	this->m_fullscreen? this->m_height=1080: this->m_height = 900;
}

ShipsView::~ShipsView() {
	this->m_surface = SDL_SetVideoMode(0,0,0, this->m_screenflags);
	if(this->m_surface)
		SDL_FreeSurface(this->m_surface);

	gluDeleteQuadric(this->obj);
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

	glClearColor(192.0f/255.0f, 0, 0, 1.0f);
	glClearDepth(1.0f);

	// Viewport set
	glViewport(0, 0, m_width, m_height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0, m_width, 0, m_height , 100, -100);

	glMatrixMode(GL_MODELVIEW);

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
	SDL_WM_SetCaption("Ships <alpha>",0);

	this->obj = gluNewQuadric();

	// Return OK
	return 0;
}

void ShipsView::Render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	    glLoadIdentity();

	    glPushMatrix();
	    glBegin(GL_QUADS);
	        glColor3f(0, 0, 0); glVertex3f(0, 0, 0);
	        glColor3f(0, 102./255, 0); glVertex3f(m_width, 0, 0);
	        glColor3f(0, 0, 0); glVertex3f(m_width, m_height, 0);
	        glColor3f(0, 0, 192./255); glVertex3f(0, m_height, 0);
	    glEnd();
	    glPopMatrix();

	    glPushMatrix();

	    m_rot += 1.;
	    o_rot += 4.;
	    glTranslatef(100.,100.+m_rot,1.);
	    //glRotatef(m_rot,0,0,1);
	    glRotatef(sin(o_rot/100)*20,0,1,0);
	    glLineWidth(1.5f);
	    glBegin(GL_LINE_LOOP);
	    	//glTranslatef(-20,-30,0);
	    	glColor3f(0,1,0);
	    	glVertex3f(0,40,0);
	    	glVertex3f(20,-30,0);
	    	glVertex3f(0,-10,0);
	    	glVertex3f(-20,-30,0);
	    glEnd();
	    glBegin(GL_LINE_STRIP);
	    	glVertex3f(0,40,0);
	    	glVertex3f(0,0,10);
	    	glVertex3f(0,-10,0);
	    glEnd();
	    glBegin(GL_LINE_STRIP);
	    	glVertex3f(20,-30,0);
	    	glVertex3f(0,0,10);
	    	glVertex3f(-20,-30,0);
	    glEnd();
	    glTranslatef(0,-20,5);
 	    	    	    	    glColor4f(1,.6,.4,0.3);
 	    	    	    	    gluSphere(this->obj, 10, 8,8);
 	    	    	    	   glColor4f(1,.7,.5,0.8);
 	    	    	    	   gluSphere(this->obj, 5, 8,8);
	    glPopMatrix();
	    glPushMatrix();
	    glTranslatef(300.,100.,1.);
	    glColor4f(1,0,0,1);
	    	    glRotatef(m_rot*1.2,0,0,1);
	    	    glRotatef(o_rot*5,0,1,0);
	    	    glLineWidth(1.6f);
	    	    glBegin(GL_LINE_LOOP);
	    	    	//glTranslatef(-20,-30,0);

	    	    	glVertex3f(0,40,0);
	    	    	glVertex3f(20,-30,0);
	    	    	glVertex3f(0,-10,0);
	    	    	glVertex3f(-20,-30,0);
	    	    glEnd();
	    	    glBegin(GL_LINE_STRIP);
	    	    	glVertex3f(0,40,0);
	    	    	glVertex3f(0,0,10);
	    	    	glVertex3f(0,-10,0);
	    	    glEnd();
	    	    glBegin(GL_LINE_STRIP);
	    	    	    	glVertex3f(20,-30,0);
	    	    	    	glVertex3f(0,0,10);
	    	    	    	glVertex3f(-20,-30,0);
	    	    glEnd();
	    	    glPopMatrix();

	    	    glPushMatrix();
	    	    	    glTranslatef(500.,100.,1.);
	    	    	    	    glRotatef(m_rot*1,0,0,-1);
	    	    	    	    glRotatef(o_rot,0,1,0);
	    	    	    	    glLineWidth(1.6f);
	    	    	    	    glColor3f(0,0.1,1.);
	    	    	    	    glBegin(GL_LINE_LOOP);
	    	    	    	    	//glTranslatef(-20,-30,0);

	    	    	    	    	glVertex3f(0,40,0);
	    	    	    	    	glVertex3f(20,-30,0);
	    	    	    	    	glVertex3f(0,-10,0);
	    	    	    	    	glVertex3f(-20,-30,0);
	    	    	    	    glEnd();
	    	    	    	    glBegin(GL_LINE_STRIP);
	    	    	    	    	glVertex3f(0,40,0);
	    	    	    	    	glVertex3f(0,0,10);
	    	    	    	    	glVertex3f(0,-10,0);
	    	    	    	    glEnd();
	    	    	    	    glBegin(GL_LINE_STRIP);
	    	    	    	    	    	glVertex3f(20,-30,0);
	    	    	    	    	    	glVertex3f(0,0,10);
	    	    	    	    	    	glVertex3f(-20,-30,0);
	    	    	    	    glEnd();

	    	    	   glPopMatrix();

	    SDL_GL_SwapBuffers();
}
