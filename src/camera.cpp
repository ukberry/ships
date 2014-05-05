/*
 * camera.cpp
 *
 *  Created on: 12 Apr 2014
 *      Author: sam
 */

#include "gamecontroller.h"

/**
 * Creates a new camera object at the specified location.
 *
 *	@param x,y	Initial position of the camera
 *	@param tc	The time constant of the camera movement.
 */
Camera::Camera(double x, double y, double tc = 200) :
	m_sensitivity(0.2), phi(0), theta(-50) {
	this->m_x = this->m_xf = x;
	this->m_y = this->m_yf = y;
	this->m_tc = tc;
	this->m_t  = 0;
}

/**
 * Moves the camera to the specified location.
 *
 * @param x,y	The location to which to move the camera.
 */
void Camera::MoveTo(double x, double y) {
	this->m_xf = x;
	this->m_yf = y;
	this->m_t = 0;
}

/**
 * Advance the game loop time.
 *
 * @param dt	The amount of time elapsed since last loop.
 */
void Camera::Loop(double dt) {
	double dx = m_xf - m_x;
	double dy = m_yf - m_y;
	this->m_t += dt;

	double A = (1. - exp(-m_t/m_tc));
	this->m_x += dx * A;
	this->m_y += dy * A;
}

void Camera::RotateBy(double phi, double theta) {
	double temp = this->theta + theta * this->m_sensitivity;
	this->theta = temp>= 0 ? 0 : (temp <= -90 ? -90 : temp);
	this->phi += phi;
}

void Camera::SetRotation(double phi, double theta) {
	this->phi = phi;
	this->theta = theta;
}

/**
 * The function called to execute code for the camera movement.
 */
void Camera::Render() {
	glRotated(this->theta,1,0,0);
	glRotated(this->phi,0,0,1);
	glTranslated(-this->m_x,-this->m_y,0);
}
