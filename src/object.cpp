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
	glPopMatrix();
}
