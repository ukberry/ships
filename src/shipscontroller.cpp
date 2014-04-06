#include "ships.h"

#include <iostream>
#include <string>
using namespace std;

// Ensure that the root controller is not set at startup.
ShipsController* ShipsController::_root = 0;

/**
 * Get the root controller instance (use this to create
 */
ShipsController* ShipsController::GetInstance() {
	if (!_root)
		_root = new ShipsController(3.14);
	return _root;
}

/**
 * Default constructor for ShipsController. This function fails as there is only
 * one controller allowed, this should be called by GetInstance.
 */
ShipsController::ShipsController() :
		m_running(true), m_state(ShipsController::State::Startup), m_view(0), m_prevState(
				0), m_active(0) {
	cerr << "ShipController class should be created directly!\n";
	throw "Controller class should not be created directly!";
}

ShipsController::ShipsController(double check) :
		m_running(true), m_state(ShipsController::State::Startup), m_view(0), m_prevState(
				0), m_active(0) {
	if (check != 3.14) {
		cerr << "ShipController class constructor sanity check value error!\n";
		throw "Check value failed!";
	}
}

ShipsController::~ShipsController() {
	// Program cleanup
	if (this->m_view)
		delete this->m_view;

	SDL_Quit();

	cout << "Ships Controller freed - Bye bye [sadface]\n";
}

int ShipsController::Init() {
	this->m_view = new ShipsView();
	if (this->m_view->CreateView())
		return 1;

	return 0;
}

#include "gamecontroller.h"

int ShipsController::Run() {

	if (this->Init()) {
		// Failed to initialise!
		cerr << "Ships failed to initialise!\n";
		return 1;
	}

	cout << "Program is running...\n";
	while (this->m_state) {
		SDL_Event evt;

		if (m_prevState != m_state && m_active) {
			// Free resources used by state controller
			delete m_active;
			m_active = 0;
		}

		this->m_prevState = this->m_state;

		switch (this->m_state) {
		case ShipsController::State::Startup:
			cout << "Welcome to Ships!\n";
			cout << "Written by Sam Berry.\n";
			this->m_state = ShipsController::State::Game;
			break;
		case ShipsController::State::Game:
			cout << "Game started.\n";
			this->m_active = new GameController();

			unsigned int ticks;
			unsigned int ticked;

			ticks = ticked= 0;
			// GameController loop
			while (this->m_running) {
				SDL_PollEvent(&evt);

				ticks = SDL_GetTicks();
				this->m_view->Render();
				if (evt.type == SDL_KEYDOWN && evt.key.keysym.sym == 'q')
					this->m_running = false;
				if (evt.type == SDL_QUIT)
					this->m_running = false;

				this->m_active->Event(evt);
				this->m_active->Loop(0);
				this->m_active->Render();
			}

			this->m_state = ShipsController::State::None;
			break;
		default:
			this->m_state = ShipsController::State::None;
			break;
		}

	}

	// If there is a controller allocated on termination, delete it.
	if(m_active) delete m_active;

	cout << "Terminate instruction received. Freeing resources!\n";
	delete ShipsController::_root;
	ShipsController::_root = 0;
	return 0;
}

