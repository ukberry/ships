/*
 * ships.h
 *
 *  Created on: 14 Jan 2014
 *      Author: sam
 */

#ifndef SHIPS_H_
#define SHIPS_H_

#include "SDL/SDL.h"

class ShipsView;
class Controller;

class ShipsController {
private:
	static ShipsController* _root;
	ShipsView* m_view;

	class State {
	public:
			static const int None = 0;
			static const int Startup = 1;
			static const int MainMenu = 2;
			static const int Options = 3;
			static const int Game = 4;
			static const int Results = 5;
		};
	int m_state;
	int m_prevState;
	int m_running;

	Controller *m_active;
public:
	static ShipsController* GetInstance();
	ShipsController();
	ShipsController(double);
	~ShipsController();

	int Init();
	int Run();

	ShipsView* GetView();
};

/**
 * Base controller class for the game states. Each must handle the Event, Loop,
 * and Render functions corresponding to the main program loop.
 */
class Controller {
public:
	Controller() {};
	virtual ~Controller() {};

public:
	virtual void Event(SDL_Event& evt) {};
	virtual void Loop(double seconds) {};
	virtual void Render() {};

};

/**
 * Base class for for something that can be rendered by the program, this is the
 * abstracted view part of the object.
 *
 * @version 1.0
 * @author Sam Berry
 */
class Renderable {
public:
	Renderable();
	virtual ~Renderable();
	virtual int Render();
};

class Ship : public Renderable {
public:
	double m_x;
	double m_y;
	double m_vx;
	double m_vy;

public:
	Ship(double x, double y);
	int Render();
	void Tick();
};



class GLUquadric;

class ShipsView {
private:
	SDL_Surface *m_surface;
	int m_screenflags;
	bool m_fullscreen;
	int m_width;
	int m_height;

public:
	ShipsView();
	~ShipsView();

	int CreateView();
	void Render();
	void Loop(double);

	int GetWidth();
	int GetHeight();
};


#endif /* SHIPS_H_ */
