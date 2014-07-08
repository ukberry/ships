/*
 * ship.cpp
 *
 *  Created on: 8 Apr 2014
 *      Author: sam
 */

#include "gamecontroller.h"
#include <cmath>
#define PI 3.14159265



Ship::Ship(float x, float y) {

	this->m_time = 0;

	this->m_x = x;
	this->m_y = y;
	this->m_z = 0;
	this->m_vx = 0;
	this->m_vy = 0;

	this->m_maxrot = 2;
	this->phi = 0;
	this->m_vr = 0;

	this->m_maxthrust = 150;
	this->m_thrust = 0;

	this->m_vtol = 0.1;
	this->m_vz = 0;

	this->m_stoppower =10;
	this->m_stop = 0;

	this->m_physics = 0;
	this->m_phystime = 0;

	this->scale = 15;
}

void Ship::Loop(unsigned int dt) {
	this->m_time += dt;
	this->phi += this->m_vr*dt;

	if(this->m_physics == 1) {
		float v 	 = sqrtf(powf(m_vx,2)+powf(m_vy,2));

		this->m_vx = -v*sinf(this->phi);
		this->m_vy = v*cosf(this->phi);
	}

	float dv = 0;

	if(this->m_stop) {
		float Theta = atan2f(this->m_vx,this->m_vy);
		std::isnan(Theta) ? Theta = 0 : 0;

		dv = this->m_stop/1e5 *this->m_maxthrust*sinf(Theta)*dt;
		fabsf(m_vx) <= fabsf(dv) ? m_vx = 0 :
		this->m_vx -= dv;

		dv = this->m_stop/1e5  *this->m_maxthrust*cosf(Theta)*dt;
		fabsf(m_vy) <= fabsf(dv) ? m_vy = 0 :
		this->m_vy -= dv;
	}
	else {
		this->m_vx += -this->m_thrust*sinf(this->phi)*dt;
		this->m_vy += this->m_thrust*cosf(this->phi)*dt;
	}

	this->m_x += this->m_vx*dt;
	this->m_y += this->m_vy*dt;

	this->m_z += this->m_vz*dt;


	float ground = 0.2*scale;
	if(m_z <= ground) {
		this->m_z = ground;
		this->yaw = 0.0;
		this->setPhysics(1);
	}
	else {
		this->setPhysics(0);
		this->yaw = 0.2*sinf(2.*M_PI * 0.4 * this->m_time/1000.);

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
	this->phi = 0;
	this->m_vx = this->m_vy = 0;
}
