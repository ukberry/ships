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

		glTranslatef(ship->m_x, ship->m_y, 0);
		glRotatef(ship->m_rot*180/PI,0,0,1);

		glLineWidth(1.7f);
		glPushMatrix();
			glBegin(GL_POLYGON);
				glColor4f(0, 0, 0, (300-ship->m_z)/300);
				glVertex3f(0, 40, 0);
				glVertex3f(20, -30, 0);
				glVertex3f(0, -10, 0);
				glVertex3f(-20, -30, 0);
			glEnd();
		glPopMatrix();

		glTranslatef(0,0,ship->m_z);
		if(!ship->m_physics)
		glRotatef(sin((ship->m_time - ship->m_phystime)*0.2 / 100) * 20, 0, 1, 0);
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

		// If the ship is thrusting, show some fire balls!
		if(ship->m_thrust) {
			glTranslatef(0, -20, 5);
			glColor4f(1, .7, .5, 0.8);
			gluSphere(this->m_sphere, 5, 8, 8);
			glColor4f(1, .6, .4, 0.3);
			gluSphere(this->m_sphere, 10, 8, 8);

			glTranslatef(-10, -10, 0);
			glColor4f(1, .7, .5, 0.8);
			gluSphere(this->m_sphere, 5, 8, 8);
			glColor4f(1, .6, .4, 0.3);
			gluSphere(this->m_sphere, 10, 8, 8);

			glTranslatef(20, 0, 0);
			glColor4f(1, .7, .5, 0.8);
			gluSphere(this->m_sphere, 5, 8, 8);
			glColor4f(1, .6, .4, 0.3);
			gluSphere(this->m_sphere, 10, 8, 8);
		}


	glPopMatrix();
}

Ship::Ship(double x, double y) {

	this->m_time = 0;

	this->m_x = x;
	this->m_y = y;
	this->m_z = 0;
	this->m_vx = 0;
	this->m_vy = 0;

	this->m_maxrot = 2;
	this->m_rot = 0;
	this->m_vr = 0;

	this->m_maxthrust = 150;
	this->m_thrust = 0;

	this->m_vtol = 0.1;
	this->m_vz = 0;

	this->m_stoppower =10;
	this->m_stop = 0;

	this->m_physics = 0;
	this->m_phystime = 0;
}

void Ship::Loop(double dt) {
	this->m_time += dt;
	this->m_rot += this->m_vr*dt;

	if(this->m_physics == 1) {
		double v 	 = sqrt(pow(m_vx,2)+pow(m_vy,2));

		this->m_vx = -v*sin(this->m_rot);
		this->m_vy = v*cos(this->m_rot);
	}

	double dv = 0;

	if(this->m_stop) {
		double theta = atan2(this->m_vx,this->m_vy);
		isnan(theta) ? theta = 0 : 0;

		dv = this->m_stop/1e5 *this->m_maxthrust*sin(theta)*dt;
		fabs(m_vx) <= fabs(dv) ? m_vx = 0 :
		this->m_vx -= dv;

		dv = this->m_stop/1e5  *this->m_maxthrust*cos(theta)*dt;
		fabs(m_vy) <= fabs(dv) ? m_vy = 0 :
		this->m_vy -= dv;
	}
	else {
		this->m_vx += -this->m_thrust*sin(this->m_rot)*dt;
		this->m_vy += this->m_thrust*cos(this->m_rot)*dt;
	}

	this->m_x += this->m_vx*dt;
	this->m_y += this->m_vy*dt;

	this->m_z += this->m_vz*dt;
	if(m_z <= 0) {
		this->m_z = 0;
		this->setPhysics(1);
	}
	else {
		this->setPhysics(0);
	}
}

void Ship::setThrust(int i) {
	this->m_thrust = i / 1e7 * this->m_maxthrust;
}

void Ship::setVz(int i){
	this->m_vz = this->m_vtol *i/100;
}

void Ship::setRotate(int i) {
	this->m_vr = i / 1e5 * this->m_maxrot;
}

void Ship::setStop(int i) {
	this->m_stop = this->m_stoppower * i/1000;
}

void Ship::setPhysics(int i) {
	if(m_physics) this->m_phystime = this->m_time;
	this->m_physics = i;

}

void Ship::resetPosition() {
	this->m_x = 0;
	this->m_y = 0;
	this->m_z = 0;
	this->m_rot = 0;
	this->m_vx = this->m_vy = 0;
}
