#include "shipsviews.h"
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

	this->v_ship->Upload();

	this->m_cam = new Camera(0,0,200);


	float width, height;
	width = height = 500.0;
	struct vertice verts[] = {
				{{-width,-height},{0.,0.},{0., 0., 1.}, {0.,1.,0.}},
				{{width,height},{0.,0.},{0., 0., 1.}, {1.,0.,0.}},
				{{width,-height},{0.,0.},{0., 0., 1.},{0.,0.,1.}}
		};

	glm::mat4 T = glm::mat4(1);
	glUniformMatrix4fv(view->GetM(), 1, GL_FALSE, glm::value_ptr(T));

	glGenVertexArrays(VAOCount, VAOs);
	glGenBuffers(BufferCount, Buffers);

	glBindVertexArray(VAOs[Test]);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[TestBuffer]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

	glVertexAttribPointer(va_coord, 2, GL_FLOAT, GL_FALSE, sizeof(struct vertice), (GLvoid*)offsetof(struct vertice,coord));
	glVertexAttribPointer(va_normal, 3, GL_FLOAT, GL_FALSE, sizeof(struct vertice), (GLvoid*)offsetof(struct vertice,normal));
	glVertexAttribPointer(va_colour, 3, GL_FLOAT, GL_FALSE, sizeof(struct vertice), (GLvoid*)offsetof(struct vertice,colour));

	glEnableVertexAttribArray(va_coord);
	glEnableVertexAttribArray(va_normal);
	glEnableVertexAttribArray(va_colour);


	struct vertice verts2[] = {
						{{-width,height,},{0.,0.},{0., 0., 1.}, {0.,0.,1.}},
						{{-width,-height},{0.,0.},{0., 0., 1.}, {0.,1.,0.}},
						{{width,height},{0.,0.},{0., 0., 1.},{1.,0.,0.}}
				};

	glBindVertexArray(VAOs[Test2]);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[OtherBuffer]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts2), verts2, GL_STATIC_DRAW);

	glVertexAttribPointer(va_coord, 2, GL_FLOAT, GL_FALSE, sizeof(struct vertice), (GLvoid*)offsetof(struct vertice,coord));
	glVertexAttribPointer(va_normal, 3, GL_FLOAT, GL_FALSE, sizeof(struct vertice), (GLvoid*)offsetof(struct vertice,normal));
	glVertexAttribPointer(va_colour, 3, GL_FLOAT, GL_FALSE, sizeof(struct vertice), (GLvoid*)offsetof(struct vertice,colour));

	glEnableVertexAttribArray(va_coord);
	glEnableVertexAttribArray(va_normal);
	glEnableVertexAttribArray(va_colour);
}

GameController::~GameController() {

	// Free rendering classes.
	delete this->v_ship;

	// Free graphics card objects
	glDeleteVertexArrays(VAOCount, VAOs);
	glDeleteBuffers(BufferCount, Buffers);

	std::vector<Ship*>::iterator it;
	for (it = this->m_ships.begin(); it != m_ships.end(); it++) {
		delete *it;
		std::cout << "Player ship deleted!\n";
	}

	delete this->m_cam;
	std::cout << "Game Controller Freed!\n";
}

void GameController::Loop(unsigned int dt) {

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

	if (SDL_GetMouseState(&mouseX, &mouseY) & SDL_BUTTON(2)) {
		this->m_cam->RotateBy(mouseX-pMouseX,pMouseY-mouseY);
	}

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
			//this->m_cam->SetRotation(-45,-50);
			}
	}
}

void GameController::Render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUniformMatrix4fv(ShipsController::GetInstance()->GetView()->GetM(),
			1,GL_FALSE,glm::value_ptr(glm::mat4(1)));
	glUniformMatrix3fv(ShipsController::GetInstance()->GetView()->GetM_inv(),
				1,GL_FALSE,glm::value_ptr(glm::mat3(1)));

	glUniform1f(ShipsController::GetInstance()->GetView()->GetisSprite(),0);
	for (int i = 0; i < VAOCount; i++) {
		glBindVertexArray(VAOs[i]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}



	this->v_ship->Render(this->m_ships[0]);

	glClear(GL_DEPTH_BUFFER_BIT);
	// Now draw the sprites

	glFlush();

	SDL_GL_SwapBuffers();
}
