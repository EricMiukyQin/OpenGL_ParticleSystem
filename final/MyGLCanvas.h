#ifndef MYGLCANVAS_H
#define MYGLCANVAS_H

#include <FL/glut.h>
#include <FL/glu.h>
#include <glm/glm.hpp>

#include <vector>
#include "Camera.h"

class ShaderManager;
class FireworkRegular;
class FireworkCone;
class FireworkCylinder;
class FireworkDisk;

class MyGLCanvas : public Fl_Gl_Window {
public:
	glm::vec3 eyePosition;
	Camera* camera;

public:
	MyGLCanvas(int x, int y, int w, int h, const char *l = 0);
	~MyGLCanvas();

	void reloadShaders();

private:
	void draw();
	void drawScene();

	void initShaders();

	int handle(int);
	void resize(int x, int y, int w, int h);
	void updateCamera(int width, int height);

	void clearFireworks();

private:
	ShaderManager* myShaderManager;
	bool firstTime;

	std::vector<FireworkRegular*> mFireworkRegulars;
	std::vector<FireworkCone*> mFireworkCones;
	std::vector<FireworkCylinder*> mFireworkCylinders;
	std::vector<FireworkDisk*> mFireworkDisks;

	// timer
	int timer;

	// mouse position
	int mouse_x, mouse_y;
};

#endif
