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
}

GameController::~GameController() {

	delete this->v_ship;

	std::vector<Ship*>::iterator it;
	for (it = this->m_ships.begin(); it != m_ships.end(); it++) {
		delete *it;
		std::cout << "Player ship deleted!\n";
	}

	std::cout << "Game Controller Freed!\n";
}

void GameController::Loop(double dt) {

	// Get the key states (event handling not that reliable for multi-key presses).
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

}

void GameController::Event(SDL_Event& evt) {

	// Catch the quit events and process them before rendering.
	if (evt.type == SDL_KEYDOWN) {
		SDLKey key = evt.key.keysym.sym;
		if (key == SDLK_g)
			this->m_ships[0]->setPhysics(1); // 1 is grip!
		if (key == SDLK_f)
			this->m_ships[0]->setPhysics(0); // 0 is free!
		if (key == SDLK_h)
			this->m_ships[0]->resetPosition();
	}
//	if (evt.type == SDL_KEYUP) {
//		SDLKey key = evt.key.keysym.sym;
//		if (key == SDLK_LEFT || key == SDLK_RIGHT)
//			this->m_ships[0]->m_vr = 0;
//
//		if (key == SDLK_SPACE)
//			this->m_ships[0]->m_thrust = 0;
//
//	}
}

void GameController::Render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glTranslated(m_width/2, m_height/2, 0);
	glRotated(-50,1,0,0);

	glRotated(this->m_rot*0.04,0,0,1);
	//glTranslated(-m_width/2, -m_height/2, 0);

	glPushMatrix();
//	glBegin(GL_QUADS);
//	glColor3f(0, 70./255, 0);
//	glVertex3f(2*-m_width, 2*-m_height, 0);
//	glColor3f(0, 102. / 255, 0);
//	glVertex3f(2*m_width, 2*-m_height, 0);
//	glColor3f(0, 60./255, 90./255);
//	glVertex3f(2*m_width, 2*m_height, 0);
//	glColor3f(0, 0, 192. / 255);
//	glVertex3f(2*-m_width, 2*m_height, 0);
//	glEnd();
	glBegin(GL_QUADS);
		int size = 400;
		glColor3f(0, 70./255, 0);
		glVertex3f(-size, -size, 0);
		glColor3f(0, 102. / 255, 0);
		glVertex3f(size, -size, 0);
		glColor3f(0, 60./255, 90./255);
		glVertex3f(size, size, 0);
		glColor3f(0, 0, 192. / 255);
		glVertex3f(-size, size, 0);
		glEnd();
	glPopMatrix();

	std::vector<Ship*>::iterator it;
	for (it = this->m_ships.begin(); it != m_ships.end(); it++) {
		this->v_ship->Render(*it);
	}

//	glPushMatrix();

//	glTranslatef(100., 100. + 400 * sin(m_rot * 0.005), 1.);
//	//glRotatef(m_rot,0,0,1);
//	glRotatef(sin(o_rot / 100) * 20, 0, 1, 0);
//	glLineWidth(1.7f);
//	glBegin(GL_LINE_LOOP);
//	//glTranslatef(-20,-30,0);
//	glColor3f(0, 1, 0);
//	glVertex3f(0, 40, 0);
//	glVertex3f(20, -30, 0);
//	glVertex3f(0, -10, 0);
//	glVertex3f(-20, -30, 0);
//	glEnd();
//	glBegin(GL_LINE_STRIP);
//	glVertex3f(0, 40, 0);
//	glVertex3f(0, 0, 10);
//	glVertex3f(0, -10, 0);
//	glEnd();
//	glBegin(GL_LINE_STRIP);
//	glVertex3f(20, -30, 0);
//	glVertex3f(0, 0, 10);
//	glVertex3f(-20, -30, 0);
//	glEnd();
//	glTranslatef(0, -20, 5);
//	glColor4f(1, .6, .4, 0.3);
//	//gluSphere(this->obj, 10, 8, 8);
//	glColor4f(1, .7, .5, 0.8);
//	//gluSphere(this->obj, 5, 8, 8);
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslatef(300. + 50 * sin(0.05 * m_rot), 100. + 50 * cos(0.05 * m_rot),
//			1.);
//	glColor4f(1, 0, 0, 1);
//	glRotatef(m_rot * 1.2, 0, 0, 1);
//	glRotatef(o_rot * 1, 0, 1, 0);
//	glLineWidth(1.6f);
//	glBegin(GL_LINE_LOOP);
//	//glTranslatef(-20,-30,0);
//	glVertex3f(0, 40, 0);
//	glVertex3f(20, -30, 0);
//	glVertex3f(0, -10, 0);
//	glVertex3f(-20, -30, 0);
//	glEnd();
//	glBegin(GL_LINE_STRIP);
//	glVertex3f(0, 40, 0);
//	glVertex3f(0, 0, 10);
//	glVertex3f(0, -10, 0);
//	glEnd();
//	glBegin(GL_LINE_STRIP);
//	glVertex3f(20, -30, 0);
//	glVertex3f(0, 0, 10);
//	glVertex3f(-20, -30, 0);
//	glEnd();
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslatef(500., 100., 1.);
//	glRotatef(m_rot * 1, 0, 0, -1);
//	glRotatef(o_rot, 0, 1, 0);
//	glLineWidth(1.6f);
//	glColor3f(0, 0.1, 1.);
//	glBegin(GL_LINE_LOOP);
//	//glTranslatef(-20,-30,0);
//	glVertex3f(0, 40, 0);
//	glVertex3f(20, -30, 0);
//	glVertex3f(0, -10, 0);
//	glVertex3f(-20, -30, 0);
//	glEnd();
//	glBegin(GL_LINE_STRIP);
//	glVertex3f(0, 40, 0);
//	glVertex3f(0, 0, 10);
//	glVertex3f(0, -10, 0);
//	glEnd();
//	glBegin(GL_LINE_STRIP);
//	glVertex3f(20, -30, 0);
//	glVertex3f(0, 0, 10);
//	glVertex3f(-20, -30, 0);
//	glEnd();
//
//	glPopMatrix();

	SDL_GL_SwapBuffers();
}
