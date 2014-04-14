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
	virtual void Loop(double seconds) {};
	virtual void Render() {};

};

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
