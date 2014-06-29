#ifndef GAMECONTROLLER_H_
#define GAMECONTROLLER_H_

#include "ships.h"

#include <iostream>
#include <vector>

#include <math.h>

typedef unsigned int GLuint;
typedef int GLint;

class ShipView;

class Ship {
	friend class ShipView;
	friend class GameController;
private:
	double m_x;
	double m_y;
	double m_z;
	double m_vx;
	double m_vy;

	double m_rot;
	double m_vr;

	double m_thrust;

	double m_maxthrust;
	double m_vtol;
	double m_vz;
	double m_maxrot;

	double m_stop;
	double m_stoppower;

	double m_time;
	double m_phystime;
	int m_physics;

public:
	Ship(double x, double y);
	void Loop(double);

	void setVz(int i);
	void setThrust(int i);
	void setRotate(int i);
	void setStop(int i);
	void setPhysics(int i);
	void resetPosition();
};

class Camera {
private:
	double m_x, m_y; 	// Current camera position
	double m_tc; 	   	// Time constant of movement
	double m_t; 		// Time since movement started
	double m_xf, m_yf; 	// Final position
	double phi, theta;
	double m_sensitivity;
public:
	Camera(double x,double y,double tc);

	void RotateBy(double phi, double theta);
	void SetRotation(double phi, double theta);
	void MoveTo(double x, double y);
	void Loop(double dt);
	void Render();

};


class GameController: public Controller {
private:
	double m_rot;
	double o_rot;
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
		va_coord, va_colour
	};

	GLuint VAOs[VAOCount];
	GLuint Buffers[BufferCount];


public:
	GameController();
	~GameController();

	void Event(SDL_Event& evt);
	void Loop(double);
	void Render();
};

#endif
