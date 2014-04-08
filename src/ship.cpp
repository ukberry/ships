/*
 * ship.cpp
 *
 *  Created on: 8 Apr 2014
 *      Author: sam
 */

#include "gamecontroller.h"
#include <cmath>
#define PI 3.14159265

ShipView::ShipView() {
	this->m_sphere = gluNewQuadric();
}


ShipView::~ShipView() {
	gluDeleteQuadric(this->m_sphere);
}

void ShipView::Render(Ship* ship) {


	glPushMatrix();

	glTranslatef(ship->m_x, ship->m_y, 1.);
	glRotatef(ship->m_rot*180/PI,0,0,1);
	glRotatef(sin(ship->m_time*0.2 / 100) * 20, 0, 1, 0);
	glLineWidth(1.7f);
	glBegin(GL_LINE_LOOP);
		//glTranslatef(-20,-30,0);
		glColor3f(1, 1, 1);
		glVertex3f(0, 40, 0);
		glVertex3f(20, -30, 0);
		glVertex3f(0, -10, 0);
		glVertex3f(-20, -30, 0);
	glEnd();
	glBegin(GL_LINE_STRIP);
		glVertex3f(0, 40, 0);
		glVertex3f(0, 0, 10);
		glVertex3f(0, -10, 0);
	glEnd();
	glBegin(GL_LINE_STRIP);
		glVertex3f(20, -30, 0);
		glVertex3f(0, 0, 10);
		glVertex3f(-20, -30, 0);
	glEnd();

	if(ship->m_thrust) {
		glTranslatef(0, -20, 5);
		glColor4f(1, .6, .4, 0.3);
		gluSphere(this->m_sphere, 10, 8, 8);
		glColor4f(1, .7, .5, 0.8);
		gluSphere(this->m_sphere, 5, 8, 8);
	}
	glPopMatrix();
}

Ship::Ship(double x, double y) {

	this->m_time = 0;

	this->m_x = x;
	this->m_y = y;
	this->m_vx = 0;
	this->m_vy = 0;

	this->m_maxrot = 5;
	this->m_rot = 0;
	this->m_vr = 0;

	this->m_maxthrust = 10;
	this->m_thrust = 0;
}

void Ship::Loop(double dt) {
	this->m_time += dt;
	this->m_rot += this->m_vr*dt;

	this->m_vx += -this->m_thrust*sin(this->m_rot)*dt;
	this->m_vy += this->m_thrust*cos(this->m_rot)*dt;

	this->m_x += this->m_vx*dt;
	this->m_y += this->m_vy*dt;


}
