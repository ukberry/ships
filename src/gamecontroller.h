#ifndef GAMECONTROLLER_H_
#define GAMECONTROLLER_H_

#include "ships.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <glm/glm.hpp>

#include <iostream>
#include <vector>

#include <math.h>

//class Controller;
class ShipView;

class Ship {
	friend class ShipView;
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

class ShipView {
private:
	GLUquadric* m_sphere;
public:
	ShipView();
	~ShipView();
	void Render(Ship* ship);
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

public:
	GameController();
	~GameController();

	void Event(SDL_Event& evt);
	void Loop(double);
	void Render();
};

#endif
