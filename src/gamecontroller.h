
#ifndef GAMECONTROLLER_H_
#define GAMECONTROLLER_H_

#include "ships.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <glm/glm.hpp>

#include <iostream>
#include <list>

#include <math.h>


class Controller;

class GameController : public Controller {
private:

public:
	GameController();
	~GameController();

	void Event(SDL_Event& evt);
	void Loop(double seconds);
	void Render();
};

#endif
