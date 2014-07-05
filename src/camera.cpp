/*
 * camera.cpp
 *
 *  Created on: 12 Apr 2014
 *      Author: sam
 */

#include "gamecontroller.h"
#include "shipsviews.h"

/**
 * Creates a new camera object at the specified location.
 *
 *	@param x,y	Initial position of the camera
 *	@param tc	The time constant of the camera movement.
 */
Camera::Camera(float x, float y, float tc = 200) :
		m_sensitivity(0.2), phi(0), theta(-50) {
	this->m_x = this->m_xf = x;
	this->m_y = this->m_yf = y;
	this->m_tc = tc;
	this->m_t = 0;

	// The camera will update the view and perspective (not so much) regularly
	// so it should maintain its own pointers to the uniform variables.
	this->m_V = ShipsController::GetInstance()->GetView()->GetV();
	this->m_P = ShipsController::GetInstance()->GetView()->GetP();
	this->m_V_inv = ShipsController::GetInstance()->GetView()->GetV_inv();

	// Distance from camera target
	this->m_distance = 10.0; //70.0;

	glm::mat4 V = glm::lookAt(
			glm::vec3(
					m_distance * cosf(-glm::radians(this->phi))
							* sinf(glm::radians(this->theta)),
					m_distance * sinf(-glm::radians(this->phi))
							* sinf(glm::radians(this->theta)),
					m_distance * cosf(glm::radians(this->theta))),
			glm::vec3(0, 0, 0), glm::vec3(0, 0, 1));

	glm::mat4 P = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f,
			10000.0f);
	glUniformMatrix4fv(this->m_V, 1, GL_FALSE, glm::value_ptr(V));
	glUniformMatrix4fv(this->m_P, 1, GL_FALSE, glm::value_ptr(P));

	glm::mat4 V_inv = glm::inverse(V);
	glUniformMatrix4fv(this->m_V_inv, 1, GL_FALSE, glm::value_ptr(V_inv));
}

/**
 * Moves the camera to the specified location.
 *
 * @param x,y	The location to which to move the camera.
 */
void Camera::MoveTo(float x, float y) {
	this->m_xf = x;
	this->m_yf = y;
	this->m_t = 0;
}

/**
 * Advance the game loop time and update the graphics card uniform variables
 * related to the view.
 *
 * @param dt	The amount of time elapsed since last loop.
 */
void Camera::Loop(unsigned int dt) {
	float dx = m_xf - m_x;
	float dy = m_yf - m_y;
	this->m_t += dt;

	//if(dx > 0 || dy > 0) {

		float A = (1. - expf(-(float)m_t / m_tc));
		this->m_x += dx * A;
		this->m_y += dy * A;
	//}

	glm::mat4 V = glm::lookAt(
			glm::vec3(
					m_x
					+ m_distance * cosf(-glm::radians(this->phi))
							* sinf(glm::radians(this->theta)),
					m_y
					+ m_distance * sinf(-glm::radians(this->phi))
							* sinf(glm::radians(this->theta)),
					m_distance * cosf(glm::radians(this->theta))),
			glm::vec3(m_xf, m_yf, 0.0f), glm::vec3(0, 0, 1));

	glUniformMatrix4fv(this->m_V, 1, GL_FALSE, glm::value_ptr(V));

	glm::mat4 V_inv = glm::inverse(V);
		glUniformMatrix4fv(this->m_V_inv, 1, GL_FALSE, glm::value_ptr(V_inv));
}

void Camera::RotateBy(float phi, float theta) {
	double temp = this->theta + theta * this->m_sensitivity;
	this->theta = temp >= 120. ? 120. : (temp <= 0.1 ? 0.1 : temp);

	this->phi += phi;
}

void Camera::SetRotation(float phi, float theta) {
	this->phi = phi;
	this->theta = theta;
}

/**
 * The function called to execute code for the camera movement.
 */
void Camera::Render() {
	// Cameras are no longer rendered!
}
