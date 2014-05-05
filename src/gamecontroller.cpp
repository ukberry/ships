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
	this->v_obj  = new ObjectView();

	/* Add a new ship to the scene (our player ship) */
	this->m_ships.push_back(new Ship(0, 0));
	std::cout << "Player ship created\n";

	this->m_cam = new Camera(0,0,200);

	this->m_objects.push_back(new Object(40,50,0,200,400,100));
	this->m_objects.push_back(new Object(90,-200,0,100,200,50));
}

GameController::~GameController() {

	// Free rendering classes.
	delete this->v_ship;
	delete this->v_obj;

	std::vector<Ship*>::iterator it;
	for (it = this->m_ships.begin(); it != m_ships.end(); it++) {
		delete *it;
		std::cout << "Player ship deleted!\n";
	}

	std::vector<Object*>::iterator it2;
		for (it2 = this->m_objects.begin(); it2 != m_objects.end(); it2++) {
			delete *it2;
			std::cout << "Object freed!\n";
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

	static int pMouseX, pMouseY;
	int mouseX, mouseY;

	if (SDL_GetMouseState(&mouseX, &mouseY) & SDL_BUTTON(2)) this->m_cam->RotateBy(mouseX-pMouseX,mouseY-pMouseY);

	pMouseX = mouseX;
	pMouseY = mouseY;

	this->m_cam->RotateBy(0.07 * dt*0.05,0);

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
		if (key == SDLK_h) {
			this->m_ships[0]->resetPosition();
			this->m_cam->SetRotation(-45,-50);
			}
	}

}

void GameController::Render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glTranslated(m_width/2, m_height/2, 0);

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

	// Draw the objects using the ObjectView class.
	std::vector<Object*>::iterator it2;
	for (it2 = this->m_objects.begin(); it2 != m_objects.end(); it2++) {
		this->v_obj->Render(*it2);
	}

	// Draw the ship based on the ShipView class passed.
	std::vector<Ship*>::iterator it;
	for (it = this->m_ships.begin(); it != m_ships.end(); it++) {
		this->v_ship->Render(*it);
	}

	glLoadIdentity();

	// Sprite graphics drawn here

	SDL_GL_SwapBuffers();
}
