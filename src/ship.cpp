/*
 * ship.cpp
 *
 *  Created on: 8 Apr 2014
 *      Author: sam
 */

#include "gamecontroller.h"
#include <cmath>
#define PI 3.14159265



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
		std::isnan(theta) ? theta = 0 : 0;

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
