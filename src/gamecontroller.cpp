#include "ships.h"
#include "gamecontroller.h"

GameController::GameController() :
		m_rot(0), o_rot(0) {
	this->obj = gluNewQuadric();

	ShipsView *view = ShipsController::GetInstance()->GetView();
	this->m_height = view->GetHeight();
	this->m_width = view->GetWidth();
	std::cout << "Game Controller Created!\n";
}

GameController::~GameController() {
	gluDeleteQuadric(this->obj);

	std::cout << "Game Controller Freed!\n";
}

void GameController::Loop(double dt) {
	m_rot += 0.07 * dt;
	o_rot += 0.2 * dt;
}

void GameController::Event(SDL_Event& evt) {

}

void GameController::Render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glPushMatrix();
	glBegin(GL_QUADS);
		glColor3f(0, 0, 0);
		glVertex3f(0, 0, 0);
		glColor3f(0, 102. / 255, 0);
		glVertex3f(m_width, 0, 0);
		glColor3f(0, 0, 0);
		glVertex3f(m_width, m_height, 0);
		glColor3f(0, 0, 192. / 255);
		glVertex3f(0, m_height, 0);
	glEnd();
	glPopMatrix();

	glPushMatrix();

	glTranslatef(100., 100. + m_rot, 1.);
	//glRotatef(m_rot,0,0,1);
	glRotatef(sin(o_rot / 100) * 20, 0, 1, 0);
	glLineWidth(1.5f);
	glBegin(GL_LINE_LOOP);
	//glTranslatef(-20,-30,0);
	glColor3f(0, 1, 0);
	glVertex3f(0, 40, 0);
	glVertex3f(20, -30, 0);
	glVertex3f(0, -10, 0);
	glVertex3f(-20, -30, 0);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex3f(0, 40, 0);
	glVertex3f(0, 0, 10);
	glVertex3f(0, -10, 0);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex3f(20, -30, 0);
	glVertex3f(0, 0, 10);
	glVertex3f(-20, -30, 0);
	glEnd();
	glTranslatef(0, -20, 5);
	glColor4f(1, .6, .4, 0.3);
	gluSphere(this->obj, 10, 8, 8);
	glColor4f(1, .7, .5, 0.8);
	gluSphere(this->obj, 5, 8, 8);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(300., 100., 1.);
	glColor4f(1, 0, 0, 1);
	glRotatef(m_rot * 1.2, 0, 0, 1);
	glRotatef(o_rot * 5, 0, 1, 0);
	glLineWidth(1.6f);
	glBegin(GL_LINE_LOOP);
	//glTranslatef(-20,-30,0);

	glVertex3f(0, 40, 0);
	glVertex3f(20, -30, 0);
	glVertex3f(0, -10, 0);
	glVertex3f(-20, -30, 0);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex3f(0, 40, 0);
	glVertex3f(0, 0, 10);
	glVertex3f(0, -10, 0);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex3f(20, -30, 0);
	glVertex3f(0, 0, 10);
	glVertex3f(-20, -30, 0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(500., 100., 1.);
	glRotatef(m_rot * 1, 0, 0, -1);
	glRotatef(o_rot, 0, 1, 0);
	glLineWidth(1.6f);
	glColor3f(0, 0.1, 1.);
	glBegin(GL_LINE_LOOP);
	//glTranslatef(-20,-30,0);

	glVertex3f(0, 40, 0);
	glVertex3f(20, -30, 0);
	glVertex3f(0, -10, 0);
	glVertex3f(-20, -30, 0);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex3f(0, 40, 0);
	glVertex3f(0, 0, 10);
	glVertex3f(0, -10, 0);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex3f(20, -30, 0);
	glVertex3f(0, 0, 10);
	glVertex3f(-20, -30, 0);
	glEnd();

	glPopMatrix();

	SDL_GL_SwapBuffers();
}
