#include "ships.h"
#include "gamecontroller.h"

GameController::GameController() :
		m_rot(0), o_rot(0) {

	ShipsView *view = ShipsController::GetInstance()->GetView();
	this->m_height = view->GetHeight();
	this->m_width = view->GetWidth();

	std::cout << "Game Controller Created!\n";

	/** This view renders each ship in the scene. */
	this->v_ship = new ShipView();

	/* Add a new ship to the scene (our player ship) */
	this->m_ships.push_back(new Ship(0, 0));
	std::cout << "Player ship created\n";

	this->m_cam = new Camera(0,0,200);
}

GameController::~GameController() {

	delete this->v_ship;

	std::vector<Ship*>::iterator it;
	for (it = this->m_ships.begin(); it != m_ships.end(); it++) {
		delete *it;
		std::cout << "Player ship deleted!\n";
	}

	delete this->m_cam;
	std::cout << "Game Controller Freed!\n";
}

void GameController::Loop(double dt) {

	// Get the key states
	Uint8* keys = SDL_GetKeyState(NULL);

	Ship* ship = this->m_ships[0];

	// If space bar pressed, set thrust to 100 percent, else set thrust to 0.
	keys[SDLK_SPACE] ? ship->setThrust(100) : ship->setThrust(0);

	// If arrow keys pressed, rotate in desired direction.
	(keys[SDLK_RIGHT] || keys[SDLK_LEFT]) ?
			ship->setRotate(keys[SDLK_LEFT]?100 :-100) : ship->setRotate(0);

	// If arrow keys pressed, rotate in desired direction.
	(keys[SDLK_x] || keys[SDLK_z]) ?
			ship->setVz(keys[SDLK_z]?-100 :100) : ship->setVz(0);

	keys[SDLK_s] && !keys[SDLK_SPACE] ? ship->setStop(100) : ship->setStop(0);

	m_rot += 0.07 * dt;
	o_rot += 0.2 * dt;

	// For each ship, execute the loop function to step through time.
	std::vector<Ship*>::size_type len = this->m_ships.size();
	for (int i = 0; i < len; i++) {
		this->m_ships[i]->Loop(dt);
	}

	// Make the camera move to the position of the ship
	this->m_cam->MoveTo(ship->m_x,ship->m_y);
	this->m_cam->Loop(dt);

}

void GameController::Event(SDL_Event& evt) {

	// Catch the quit events and process them before rendering.
	if (evt.type == SDL_KEYDOWN) {
		SDLKey key = evt.key.keysym.sym;
		if (key == SDLK_h)
			this->m_ships[0]->resetPosition();
	}

}

void GameController::Render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glTranslated(m_width/2, m_height/2, 0);
	glRotated(-50,1,0,0);

	glRotated(this->m_rot*0.04,0,0,1);
	//glTranslated(-m_width/2, -m_height/2, 0);

	// Add camera position
	this->m_cam->Render();

	// Landscape drawing
	glPushMatrix();
	glBegin(GL_QUADS);
		int size = 800;
		glColor3f(0.9, 70./255, 0);
		glVertex3f(-size, -size, -1);
		glColor3f(0, 102. / 255, 0);
		glVertex3f(size, -size, -1);
		glColor3f(0, 60./255, 90./255);
		glVertex3f(size, size, -1);
		glColor3f(0, 0, 192. / 255);
		glVertex3f(-size, size, -1);
		glEnd();
	glPopMatrix();

	std::vector<Ship*>::iterator it;
	for (it = this->m_ships.begin(); it != m_ships.end(); it++) {
		this->v_ship->Render(*it);
	}

	glLoadIdentity();

	// Sprite graphics drawn here

	SDL_GL_SwapBuffers();
}
