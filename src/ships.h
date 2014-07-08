/*
 * ships.h
 *
 *  Created on: 14 Jan 2014
 *      Author: sam
 */

#ifndef SHIPS_H_
#define SHIPS_H_

#define SHIP_CONTROLLER_MAIN 3.14789632

#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <SDL/SDL.h>

class ShipsView;
class Controller;

/**
 * The main program controller, handles the application states.
 */
class ShipsController {
private:
	/// Reference to the root controller instance
	static ShipsController* _root;

	/// Handle to the main view (usually the master window).
	ShipsView* m_view;

	/**
	 * Define the set of games states.
	 *
	 * I can't remember why I didn't use an enumeration here!?
	 */
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

	/// A pointer to the active game state controller.
	Controller *m_active;
public:
	/**
	 * Returns the main application controller
	 *
	 * @return ShipController* The main application controller.
	 */
	static ShipsController* GetInstance();

	// Constructors and Destructor
	ShipsController();
	ShipsController(double);
	~ShipsController();

	int Init();
	int Run();

	/// Return the main view class used by the controller.
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
	virtual void Loop(unsigned int seconds) {};
	virtual void Render() {};

};

class ShipsView {
private:
	SDL_Surface *m_surface;
	int m_screenflags;
	bool m_fullscreen;
	int m_width;
	int m_height;

	GLint m_program;
	GLint m_uniM;
	GLint m_uniV;
	GLint m_uniP;
	GLint m_uniV_inv;
	GLint m_uniM_inv;
	GLint m_uniisSprite;
	GLint m_uniVSprite;

public:
	ShipsView();
	~ShipsView();

	int CreateView();

	int GetWidth();
	int GetHeight();
	GLuint GetGraphicsProg();
	GLint GetM();
	GLint GetV();
	GLint GetP();
	GLint GetV_inv();
	GLint GetM_inv();
	GLint GetisSprite();
	GLint GetVSprite();
};



#endif /* SHIPS_H_ */
