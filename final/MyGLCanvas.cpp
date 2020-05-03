#if defined(__APPLE__)
#  include <OpenGL/gl3.h> // defines OpenGL 3.0+ functions
#else
#  if defined(WIN32)
#    define GLEW_STATIC 1
#  endif
#  include <GL/glew.h>
#endif

#include "MyGLCanvas.h"
#include "ShaderManager.h"
#include "FireworkRegular.h"
#include "FireworkCone.h"
#include "FireworkCylinder.h"
#include "FireworkDisk.h"
#include "Util.h"


MyGLCanvas::MyGLCanvas(int x, int y, int w, int h, const char *l)
	: Fl_Gl_Window(x, y, w, h, l), firstTime{ true }, timer{ 0 } {
	mode(FL_RGB | FL_ALPHA | FL_DEPTH | FL_DOUBLE);
	eyePosition = glm::vec3(3.f, 4.f, 6.f);
	camera = new Camera();
	camera->orientLookAt(eyePosition, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	myShaderManager = new ShaderManager();

	// initialize mouse position
	mouse_x = (int)Fl::event_x();
	mouse_y = (int)Fl::event_y();
}


MyGLCanvas::~MyGLCanvas() {
	delete camera;
	delete myShaderManager;
	clearFireworks();
}

void MyGLCanvas::draw() {
	if (!valid()) {  //this is called when the GL canvas is set up for the first time or when it is resized...
		printf("establishing GL context\n");

		glViewport(0, 0, w(), h());
		updateCamera(w(), h());

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

		/****************************************/
		/*          Enable z-buferring          */
		/****************************************/

		glEnable(GL_DEPTH_TEST);
		glPolygonOffset(1, 1);
		//glFrontFace(GL_CCW); //make sure that the ordering is counter-clock wise
		//glEnable(GL_RESCALE_NORMAL);

		if (firstTime == true) {
			firstTime = false;
			initShaders();
		}
	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	drawScene();
}

void MyGLCanvas::drawScene() {
	//SHADER: passing the projection matrix to the shader... the projection matrix will be called myProjectionMatrix in shader
	glUniformMatrix4fv(glGetUniformLocation(myShaderManager->program, "myModelviewMatrix"), 1, false, glm::value_ptr(camera->getModelViewMatrix()));

	// if timer is in mFireTimes, new firesworks
	if (FIREWORK_TIMES.count(timer) == 1) {
		switch (Util::RandFireworkType()) {
		case FireworkType::FIREWORK_REGULAR:
			mFireworkRegulars.push_back(
				new FireworkRegular(
					myShaderManager,
					glm::vec3{ Util::RandFloat(-200.f, 200.f), Util::RandFloat(-100.f, 5.f), Util::RandFloat(-200.f, 200.f) },
					glm::vec3{ .01f, .01f, .01f },
					1000,
					10,
					Util::RandColor()
				)
			);

			mFireworkRegulars.back()->BuildArrays();
			mFireworkRegulars.back()->BindVBO(myShaderManager->program);
			break;
		case FireworkType::FIREWORK_CONE:
			mFireworkCones.push_back(
				new FireworkCone(
					myShaderManager,
					glm::vec3{ Util::RandFloat(-200.f, 200.f), Util::RandFloat(-100.f, 5.f), Util::RandFloat(-200.f, 200.f) },
					glm::vec3{ .01f, .01f, .01f },
					1000,
					10,
					Util::RandColor()
				)
			);

			mFireworkCones.back()->BuildArrays();
			mFireworkCones.back()->BindVBO(myShaderManager->program);
			break;
		case FireworkType::FIREWORK_CYLINDER:
			mFireworkCylinders.push_back(
				new FireworkCylinder(
					myShaderManager,
					glm::vec3{ Util::RandFloat(-200.f, 200.f), Util::RandFloat(-100.f, 5.f), Util::RandFloat(-200.f, 200.f) },
					glm::vec3{ .01f, .01f, .01f },
					1000,
					10,
					Util::RandColor()
				)
			);

			mFireworkCylinders.back()->BuildArrays();
			mFireworkCylinders.back()->BindVBO(myShaderManager->program);
			break;
		case FireworkType::FIREWORK_DISK:
			mFireworkDisks.push_back(
				new FireworkDisk(
					myShaderManager,
					glm::vec3{ Util::RandFloat(-200.f, 200.f), Util::RandFloat(-100.f, 5.f), Util::RandFloat(-200.f, 200.f) },
					glm::vec3{ .01f, .01f, .01f },
					1000,
					10,
					Util::RandColor()
				)
			);

			mFireworkDisks.back()->BuildArrays();
			mFireworkDisks.back()->BindVBO(myShaderManager->program);
			break;
		default:
			break;
		}
	}

	//renders the object
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	for (const auto& fireworkRegular : mFireworkRegulars) {
		fireworkRegular->Render();
		fireworkRegular->Update(DELTA_T);
	}

	for (const auto& fireworkCone : mFireworkCones) {
		fireworkCone->Render();
		fireworkCone->Update(DELTA_T);
	}

	for (const auto& fireworkCylinder : mFireworkCylinders) {
		fireworkCylinder->Render();
		fireworkCylinder->Update(DELTA_T);
	}

	for (const auto& fireworkDisk : mFireworkDisks) {
		fireworkDisk->Render();
		fireworkDisk->Update(DELTA_T);
	}

	// update timer
	++timer;
}

int MyGLCanvas::handle(int e) {
	//static int first = 1;
#ifndef __APPLE__
	if (firstTime && e == FL_SHOW && shown()) {
		firstTime = 0;
		make_current();
		GLenum err = glewInit(); // defines pters to functions of OpenGL V 1.2 and above
		if (GLEW_OK != err) {
			/* Problem: glewInit failed, something is seriously wrong. */
			fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		}
		else {
			//SHADER: initialize the shader manager and loads the two shader programs
			initShaders();
		}
	}
#endif	
	//printf("Event was %s (%d)\n", fl_eventnames[e], e);
	switch (e) {
	case FL_ENTER: cursor(FL_CURSOR_HAND); break;
	case FL_LEAVE: cursor(FL_CURSOR_DEFAULT); break;
	case FL_MOVE:
		Fl::belowmouse(this);
		// mouse move left-right
		camera->rotateV(Util::Clamp<float>((mouse_x - (int)Fl::event_x()) * .01f, -PI / 2.f, PI / 2.f));
		mouse_x = (int)Fl::event_x();

		// mouse move top-down
		camera->rotateU(Util::Clamp<float>((mouse_y - (int)Fl::event_y()) * .01f, -PI / 2.f, PI / 2.f));
		mouse_y = (int)Fl::event_y();
		break;
	case FL_KEYUP:
		printf("keyboard event: key pressed: %c\n", Fl::event_key());
		switch (Fl::event_key()) {
			case 'w':
				camera->translate(camera->getLookVector() * .3f);
				break;
			case 's':
				camera->translate(camera->getLookVector() * -.3f);
				break;
			case 'a':
				camera->translate(glm::cross(camera->getUpVector(), camera->getLookVector()) * .3f);
				break;
			case 'd':
				camera->translate(glm::cross(camera->getUpVector(), camera->getLookVector()) * -.3f);
				break;
		}
		updateCamera(w(), h());
		break;
	default:
		break;
	}
	return Fl_Gl_Window::handle(e);
}


void MyGLCanvas::resize(int x, int y, int w, int h) {
	Fl_Gl_Window::resize(x, y, w, h);
	puts("resize called");
}


void MyGLCanvas::initShaders() {
	myShaderManager->initShader("shaders/330/VertexShader.vert", "shaders/330/FragmentShader.frag");
}


void MyGLCanvas::reloadShaders() {
	// clear fireworks
	clearFireworks();

	// reset shaders
	myShaderManager->resetShaders();

	// reset timer and firstTime
	timer = 0;
	firstTime = true;

	// reset camera
	eyePosition = glm::vec3(3.f, 4.f, 6.f);
	camera->orientLookAt(eyePosition, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
}


void MyGLCanvas::updateCamera(int width, int height) {
	float xy_aspect;
	xy_aspect = (float)width / (float)height;
	camera->setScreenSize(width, height);
	glUniformMatrix4fv(glGetUniformLocation(myShaderManager->program, "myProjectionMatrix"), 1, false, glm::value_ptr(camera->getProjectionMatrix()));
}


void MyGLCanvas::clearFireworks() {
	for (int i = 0; i < mFireworkRegulars.size(); ++i)
		delete mFireworkRegulars[i];

	for (int i = 0; i < mFireworkCones.size(); ++i)
		delete mFireworkCones[i];

	for (int i = 0; i < mFireworkCylinders.size(); ++i)
		delete mFireworkCylinders[i];

	for (int i = 0; i < mFireworkDisks.size(); ++i)
		delete mFireworkDisks[i];

	std::vector<FireworkRegular*>().swap(mFireworkRegulars);
	std::vector<FireworkCone*>().swap(mFireworkCones);
	std::vector<FireworkCylinder*>().swap(mFireworkCylinders);
	std::vector<FireworkDisk*>().swap(mFireworkDisks);
}

