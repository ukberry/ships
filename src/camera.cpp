/*
 * camera.cpp
 *
 *  Created on: 12 Apr 2014
 *      Author: sam
 */

#include "gamecontroller.h"

Camera::Camera(double x, double y, double tc) {
	this->m_x = this->m_xf = x;
	this->m_y = this->m_yf = y;
	this->m_tc = tc;
	this->m_t  = 0;
}

void Camera::MoveTo(double x, double y) {
	this->m_xf = x;
	this->m_yf = y;
	this->m_t = 0;
}

void Camera::Loop(double dt) {
	double dx = m_xf - m_x;
	double dy = m_yf - m_y;
	this->m_t += dt;

	double A = (1. - exp(-m_t/m_tc));
	this->m_x += dx * A;
	this->m_y += dy * A;
}

void Camera::Render() {
	glTranslated(-this->m_x,-this->m_y,0);
}
