/*
 * object.cpp
 *
 *  Created on: 14 Apr 2014
 *      Author: sam
 */

#include "object.h"

#include <GL/gl.h>

Object::Object(double x, double y, double z,
		double length, double width, double height) :
		m_x(x), m_y(y), m_z(z), m_length(length), m_width(width), m_height(height) {

}

void ObjectView::Render(Object* obj) {
	glPushMatrix();
		glTranslatef(obj->m_x, obj->m_y, 0);
		glBegin(GL_POLYGON);
			glColor3f(.7,.7,.7);
			glVertex3f(-obj->m_width/2,	-obj->m_length/2,obj->m_height);
			glVertex3f(-obj->m_width/2,	obj->m_length/2,obj->m_height);
			glVertex3f(obj->m_width/2,	obj->m_length/2,obj->m_height);
			glVertex3f(obj->m_width/2, 	-obj->m_length/2,obj->m_height);
		glEnd();
		glBegin(GL_LINE_LOOP);
			glVertex3f(obj->m_width/2, 	-obj->m_length/2,obj->m_height);
			glVertex3f(obj->m_width/2, 	-obj->m_length/2, 0);
			glVertex3f(obj->m_width/2, 	obj->m_length/2, 0);
			glVertex3f(obj->m_width/2, 	obj->m_length/2, obj->m_height);
		glEnd();
		glBegin(GL_LINE_LOOP);
			glVertex3f(obj->m_width/2, 	obj->m_length/2,obj->m_height);
			glVertex3f(obj->m_width/2, 	obj->m_length/2, 0);
			glVertex3f(-obj->m_width/2, 	obj->m_length/2, 0);
			glVertex3f(-obj->m_width/2, 	obj->m_length/2, obj->m_height);
		glEnd();
		glBegin(GL_LINE_LOOP);
			glVertex3f(-obj->m_width/2, 	obj->m_length/2,obj->m_height);
			glVertex3f(-obj->m_width/2, 	obj->m_length/2, 0);
			glVertex3f(-obj->m_width/2, 	-obj->m_length/2, 0);
			glVertex3f(-obj->m_width/2, 	-obj->m_length/2, obj->m_height);
		glEnd();
		glBegin(GL_LINE_LOOP);
			glVertex3f(-obj->m_width/2, 	-obj->m_length/2,obj->m_height);
			glVertex3f(-obj->m_width/2, 	-obj->m_length/2, 0);
			glVertex3f(obj->m_width/2, 	-obj->m_length/2, 0);
			glVertex3f(obj->m_width/2, 	-obj->m_length/2, obj->m_height);
		glEnd();
	glPopMatrix();
}
