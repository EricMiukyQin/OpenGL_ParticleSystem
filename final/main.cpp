#include <string>
#include <iostream>
#include <fstream>
#include <math.h>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Pack.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Value_Slider.H>
#include <FL/Fl_File_Chooser.H>
#include <FL/Fl_Gl_Window.H>
#include <FL/names.h>

#include "MyGLCanvas.h"


using namespace std;

class MyAppWindow;
MyAppWindow *win;

class MyAppWindow : public Fl_Window {
public:
	//Fl_Slider* rotXSlider;
	//Fl_Slider* rotYSlider;
	//Fl_Slider* rotZSlider;
	//Fl_Slider* scaleSlider;

	//Fl_Slider* rotUSlider;
	//Fl_Slider* rotVSlider;
	//Fl_Slider* rotWSlider;

	//Fl_Slider* eyeXSlider;
	//Fl_Slider* eyeYSlider;
	//Fl_Slider* eyeZSlider;

	//Fl_Slider* lookXSlider;
	//Fl_Slider* lookYSlider;
	//Fl_Slider* lookZSlider;

	//Fl_Slider* nearSlider;
	//Fl_Slider* farSlider;
	//Fl_Slider* angleSlider;

	Fl_Button* resetButton;

	MyGLCanvas* canvas;

public:
	// APP WINDOW CONSTRUCTOR
	MyAppWindow(int W, int H, const char*L = 0);

	static void idleCB(void* userdata) {
		win->canvas->redraw();
	}

private:
	// Someone changed one of the sliders
	//static void toggleCB(Fl_Widget* w, void* userdata) {
	//	int value = ((Fl_Button*)w)->value();
	//	printf("value: %d\n", value);
	//	*((int*)userdata) = value;
	//}

	//static void sliderFloatCB(Fl_Widget* w, void* userdata) {
	//	float value = ((Fl_Slider*)w)->value();
	//	printf("value: %f\n", value);
	//	*((float*)userdata) = value;
	//}

	//static void cameraRotateCB(Fl_Widget* w, void* userdata) {
	//	win->canvas->camera->setRotUVW(win->rotUSlider->value(), win->rotVSlider->value(), win->rotWSlider->value());
	//	glm::vec3 lookV = win->canvas->camera->getLookVector();
	//	lookV = glm::normalize(lookV);
	//	win->lookXSlider->value(lookV.x);
	//	win->lookYSlider->value(lookV.y);
	//	win->lookZSlider->value(lookV.z);
	//}

	//static void cameraEyeCB(Fl_Widget* w, void* userdata) {
	//	float eyeX = win->eyeXSlider->value();
	//	float eyeY = win->eyeYSlider->value();
	//	float eyeZ = win->eyeZSlider->value();
	//	win->canvas->camera->orientLookVec(glm::vec3(eyeX, eyeY, eyeZ), win->canvas->camera->getLookVector(), win->canvas->camera->getUpVector());
	//}

	//static void cameraLookCB(Fl_Widget* w, void* userdata) {
	//	float lookX = win->lookXSlider->value();
	//	float lookY = win->lookYSlider->value();
	//	float lookZ = win->lookZSlider->value();
	//	win->canvas->camera->orientLookVec(win->canvas->camera->getEyePoint(), glm::vec3(lookX, lookY, lookZ), win->canvas->camera->getUpVector());
	//}

	//static void camPropCB(Fl_Widget* w, void* userdata) {
	//	float nearVal = win->nearSlider->value();
	//	float farVal = win->farSlider->value();
	//	float angle = win->angleSlider->value();

	//	win->canvas->camera->setNearPlane(nearVal);
	//	win->canvas->camera->setFarPlane(farVal);
	//	win->canvas->camera->setViewAngle(angle);
	//}

	static void resetCB(Fl_Widget* w, void* userdata) {
		win->canvas->reloadShaders();
	}
};


MyAppWindow::MyAppWindow(int W, int H, const char*L) : Fl_Window(W, H, L) {
	begin();

	canvas = new MyGLCanvas(10, 10, w() - 110, h() - 20);

	Fl_Pack* pack = new Fl_Pack(w() - 100, 30, 100, h());
	pack->box(FL_DOWN_FRAME);
	pack->labelfont(1);
	pack->type(Fl_Pack::VERTICAL);
	pack->spacing(20);
	pack->begin();

	//Fl_Pack* rotPack = new Fl_Pack(w() - 100, 30, 100, h(), "Rotate");
	//rotPack->box(FL_DOWN_FRAME);
	//rotPack->labelfont(1);
	//rotPack->type(Fl_Pack::VERTICAL);
	//rotPack->spacing(0);
	//rotPack->begin();

	//Fl_Box *rotUTextBox = new Fl_Box(0, 0, pack->w() - 20, 20, "RotateU");
	//rotUSlider = new Fl_Value_Slider(0, 0, pack->w() - 20, 20, "");
	//rotUSlider->align(FL_ALIGN_TOP);
	//rotUSlider->type(FL_HOR_SLIDER);
	//rotUSlider->bounds(-179, 179);
	//rotUSlider->step(1);
	//rotUSlider->value(canvas->camera->rotU);
	//rotUSlider->callback(cameraRotateCB);

	//Fl_Box *rotVTextBox = new Fl_Box(0, 0, pack->w() - 20, 20, "RotateV");
	//rotVSlider = new Fl_Value_Slider(0, 0, pack->w() - 20, 20, "");
	//rotVSlider->align(FL_ALIGN_TOP);
	//rotVSlider->type(FL_HOR_SLIDER);
	//rotVSlider->bounds(-179, 179);
	//rotVSlider->step(1);
	//rotVSlider->value(canvas->camera->rotV);
	//rotVSlider->callback(cameraRotateCB);

	//Fl_Box *rotWTextBox = new Fl_Box(0, 0, pack->w() - 20, 20, "RotateW");
	//rotWSlider = new Fl_Value_Slider(0, 0, pack->w() - 20, 20, "");
	//rotWSlider->align(FL_ALIGN_TOP);
	//rotWSlider->type(FL_HOR_SLIDER);
	//rotWSlider->bounds(-179, 179);
	//rotWSlider->step(1);
	//rotWSlider->value(canvas->camera->rotW);
	//rotWSlider->callback(cameraRotateCB);

	//rotPack->end();

	//Fl_Pack* eyePack = new Fl_Pack(w() - 100, 30, 100, h(), "Eye");
	//eyePack->box(FL_DOWN_FRAME);
	//eyePack->labelfont(1);
	//eyePack->type(Fl_Pack::VERTICAL);
	//eyePack->spacing(0);
	//eyePack->begin();

	//Fl_Box *eyeXTextBox = new Fl_Box(0, 0, pack->w() - 20, 20, "EyeX");
	//eyeXSlider = new Fl_Value_Slider(0, 0, pack->w() - 20, 20, "");
	//eyeXSlider->align(FL_ALIGN_TOP);
	//eyeXSlider->type(FL_HOR_SLIDER);
	//eyeXSlider->bounds(-5, 5);
	//eyeXSlider->value(canvas->camera->getEyePoint()[0]);
	//eyeXSlider->callback(cameraEyeCB);

	//Fl_Box *eyeYTextBox = new Fl_Box(0, 0, pack->w() - 20, 20, "EyeY");
	//eyeYSlider = new Fl_Value_Slider(0, 0, pack->w() - 20, 20, "");
	//eyeYSlider->align(FL_ALIGN_TOP);
	//eyeYSlider->type(FL_HOR_SLIDER);
	//eyeYSlider->bounds(-5, 5);
	//eyeYSlider->value(canvas->camera->getEyePoint()[1]);
	//eyeYSlider->callback(cameraEyeCB);

	//Fl_Box *eyeZTextBox = new Fl_Box(0, 0, pack->w() - 20, 20, "EyeZ");
	//eyeZSlider = new Fl_Value_Slider(0, 0, pack->w() - 20, 20, "");
	//eyeZSlider->align(FL_ALIGN_TOP);
	//eyeZSlider->type(FL_HOR_SLIDER);
	//eyeZSlider->bounds(-5, 5);
	//eyeZSlider->value(canvas->camera->getEyePoint()[2]);
	//eyeZSlider->callback(cameraEyeCB);
	//eyePack->end();


	//Fl_Pack* lookPack = new Fl_Pack(w() - 100, 30, 100, h(), "LookVec");
	//lookPack->box(FL_DOWN_FRAME);
	//lookPack->labelfont(1);
	//lookPack->type(Fl_Pack::VERTICAL);
	//lookPack->spacing(0);
	//lookPack->begin();

	//Fl_Box *lookXTextBox = new Fl_Box(0, 0, pack->w() - 20, 20, "LookX");
	//lookXSlider = new Fl_Value_Slider(0, 0, pack->w() - 20, 20, "");
	//lookXSlider->align(FL_ALIGN_TOP);
	//lookXSlider->type(FL_HOR_SLIDER);
	//lookXSlider->bounds(-5, 5);
	//lookXSlider->value(canvas->camera->getLookVector()[0]);
	//lookXSlider->callback(cameraLookCB);

	//Fl_Box *lookYTextBox = new Fl_Box(0, 0, pack->w() - 20, 20, "LookY");
	//lookYSlider = new Fl_Value_Slider(0, 0, pack->w() - 20, 20, "");
	//lookYSlider->align(FL_ALIGN_TOP);
	//lookYSlider->type(FL_HOR_SLIDER);
	//lookYSlider->bounds(-5, 5);
	//lookYSlider->value(canvas->camera->getLookVector()[1]);
	//lookYSlider->callback(cameraLookCB);

	//Fl_Box *lookZTextBox = new Fl_Box(0, 0, pack->w() - 20, 20, "LookZ");
	//lookZSlider = new Fl_Value_Slider(0, 0, pack->w() - 20, 20, "");
	//lookZSlider->align(FL_ALIGN_TOP);
	//lookZSlider->type(FL_HOR_SLIDER);
	//lookZSlider->bounds(-5, 5);
	//lookZSlider->value(canvas->camera->getLookVector()[2]);
	//lookZSlider->callback(cameraLookCB);

	//lookPack->end();


	//Fl_Pack* camPropPack = new Fl_Pack(w() - 100, 30, 100, h(), "Properties");
	//camPropPack->box(FL_DOWN_FRAME);
	//camPropPack->labelfont(1);
	//camPropPack->type(Fl_Pack::VERTICAL);
	//camPropPack->spacing(0);
	//camPropPack->begin();

	//Fl_Box *nearTextBox = new Fl_Box(0, 0, pack->w() - 20, 20, "Near");
	//nearSlider = new Fl_Value_Slider(0, 0, pack->w() - 20, 20, "");
	//nearSlider->align(FL_ALIGN_TOP);
	//nearSlider->type(FL_HOR_SLIDER);
	//nearSlider->bounds(0.01, 10);
	//nearSlider->value(canvas->camera->getNearPlane());
	//nearSlider->callback(camPropCB);

	//Fl_Box *farTextBox = new Fl_Box(0, 0, pack->w() - 20, 20, "Far");
	//farSlider = new Fl_Value_Slider(0, 0, pack->w() - 20, 20, "");
	//farSlider->align(FL_ALIGN_TOP);
	//farSlider->type(FL_HOR_SLIDER);
	//farSlider->bounds(0.01, 30);
	//farSlider->value(canvas->camera->getFarPlane());
	//farSlider->callback(camPropCB);

	//Fl_Box *angleTextBox = new Fl_Box(0, 0, pack->w() - 20, 20, "Angle");
	//angleSlider = new Fl_Value_Slider(0, 0, pack->w() - 20, 20, "");
	//angleSlider->align(FL_ALIGN_TOP);
	//angleSlider->type(FL_HOR_SLIDER);
	//angleSlider->bounds(1, 179);
	//angleSlider->step(1);
	//angleSlider->value(canvas->camera->getViewAngle());
	//angleSlider->callback(camPropCB);

	resetButton = new Fl_Button(0, 0, pack->w() - 20, 20, "Reload");
	resetButton->callback(resetCB, (void*)this);

	//camPropPack->end();
	end();
}


/**************************************** main() ********************/
int main(int argc, char **argv) {
	win = new MyAppWindow(850, 650, "Firework");
	win->resizable(win);
	Fl::add_idle(MyAppWindow::idleCB);
	win->show();
	return(Fl::run());
}
