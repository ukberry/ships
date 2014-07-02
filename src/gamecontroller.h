#ifndef GAMECONTROLLER_H_
#define GAMECONTROLLER_H_

#include "ships.h"
#include "object.h"

#include <iostream>
#include <vector>

#include <math.h>

typedef unsigned int GLuint;
typedef int GLint;

class ShipView;

class Ship : public ObjectModel {
	friend class ShipView;
	friend class GameController;
private:
	float m_vx;
	float m_vy;

	float m_vr;

	float m_thrust;

	float m_maxthrust;
	float m_vtol;
	float m_vz;
	float m_maxrot;

	float m_stop;
	float m_stoppower;

	unsigned int m_time;
	float m_phystime;
	int m_physics;

public:
	Ship(float x, float y);
	void Loop(unsigned int);

	void setVz(int i);
	void setThrust(int i);
	void setRotate(int i);
	void setStop(int i);
	void setPhysics(int i);
	void resetPosition();
};

class Camera {
private:
	float m_x, m_y; 	// Current camera position
	float m_tc; 	   	// Time constant of movement
	unsigned int m_t; 		// Time since movement started
	float m_xf, m_yf; 	// Final position

	float m_distance;
	float phi, theta;
	float m_sensitivity;

	// The camera maintains its own reference to the OpenGL V and P uniforms.
	GLint m_V;
	GLint m_P;
	GLint m_V_inv;
public:
	Camera(float x,float y,float tc);

	void RotateBy(float phi, float theta);
	void SetRotation(float phi, float theta);
	void MoveTo(float x, float y);
	void Loop(unsigned int dt);
	void Render();

};


class GameController: public Controller {
private:
	float m_rot;
	float o_rot;
	int m_width, m_height;

	// Models
	std::vector<Ship*> m_ships;

	// Rendering views
	ShipView* v_ship;

	/// Reference to the Camera
	Camera* m_cam;

	//
	enum VAO_indices {
		Test, Test2, VAOCount
	};
	enum Buffer_indices {
		TestBuffer, OtherBuffer, BufferCount
	};

	enum Vertice_attributes {
		va_coord, va_texcoord, va_normal, va_colour
	};

	GLuint VAOs[VAOCount];
	GLuint Buffers[BufferCount];


public:
	GameController();
	~GameController();

	void Event(SDL_Event& evt);
	void Loop(unsigned int);
	void Render();
};

#endif
