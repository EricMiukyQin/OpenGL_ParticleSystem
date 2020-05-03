#include "Camera.h"

using namespace glm;

Camera::Camera() {
	reset();
}

Camera::~Camera() {
}

void Camera::reset() {
	orientLookAt(glm::vec3(0.0f, 0.0f, DEFAULT_FOCUS_LENGTH), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	setViewAngle(VIEW_ANGLE);
	setNearPlane(NEAR_PLANE);
	setFarPlane(FAR_PLANE);
	screenWidth = screenHeight = 200;
	screenWidthRatio = 1.0f;
	rotU = rotV = rotW = 0;
}

//called by main.cpp as a part of the slider callback for controlling rotation
// the reason for computing the diff is to make sure that we are only incrementally rotating the camera
void Camera::setRotUVW(float u, float v, float w) {
	float diffU = u - rotU;
	float diffV = v - rotV;
	float diffW = w - rotW;
	rotateU(diffU);
	rotateV(diffV);
	rotateW(diffW);
	rotU = u;
	rotV = v;
	rotW = w;
}

void Camera::orientLookAt(glm::vec3 eyePoint, glm::vec3 lookatPoint, glm::vec3 upVec) {
	orientLookVec(eyePoint, lookatPoint - eyePoint, upVec);
}

void Camera::orientLookVec(glm::vec3 eyePoint, glm::vec3 lookVec, glm::vec3 upVec) {
	m_eye = eyePoint;
	m_look = normalize(lookVec);
	m_up = normalize(upVec);
}

glm::mat4 Camera::getScaleMatrix() {
	return mat4{
		1 / (tanf(radians(viewAngle) / 2) * farPlane), 0.f, 0.f, 0.f,
		0.f, screenWidthRatio / (tanf(radians(viewAngle) / 2) * farPlane), 0.f, 0.f,
		0.f, 0.f, 1.f / farPlane, 0.f,
		0.f, 0.f, 0.f, 1.f
	};
}

glm::mat4 Camera::getInverseScaleMatrix() {
	return inverse(getScaleMatrix());
}

glm::mat4 Camera::getUnhingeMatrix() {
	float c = -nearPlane / farPlane;
	return mat4{
		1.f, 0.f, 0.f, 0.f,
		0.f, 1.f, 0.f, 0.f,
		0.f, 0.f, -1.f / (c + 1.f), -1.f,
		0.f, 0.f, c / (c + 1.f), 0.f
	};
}

glm::mat4 Camera::getProjectionMatrix() {
	return getUnhingeMatrix() * getScaleMatrix();
}

glm::mat4 Camera::getInverseModelViewMatrix() {
	return glm::inverse(getModelViewMatrix());
}

void Camera::setViewAngle (float _viewAngle) {
	viewAngle = _viewAngle;
}

void Camera::setNearPlane (float _nearPlane) {
	nearPlane = _nearPlane;
}

void Camera::setFarPlane (float _farPlane) {
	farPlane = _farPlane;
}

void Camera::setScreenSize (int _screenWidth, int _screenHeight) {
	screenWidth = _screenWidth;
	screenHeight = _screenHeight;
	screenWidthRatio = (float)screenWidth / (float)screenHeight;
}

glm::mat4 Camera::getInverseRotateMatrix() {
	vec3 w = normalize(-m_look);
	vec3 u = normalize(cross(m_up, w));
	vec3 v = normalize(cross(w, u));
	glm::mat4 theMat = mat4{
			u.x, v.x, w.x, 0.f,
			u.y, v.y, w.y, 0.f,
			u.z, v.z, w.z, 0.f,
			0.f, 0.f, 0.f, 1.f
	};
	return glm::inverse(theMat);
}

glm::mat4 Camera::getInverseTranslateMatrix() {
	vec3 w = normalize(-m_look);
	vec3 u = normalize(cross(m_up, w));
	vec3 v = normalize(cross(w, u));
	glm::mat4 theMat = mat4{
			1.f, 0.f, 0.f, 0.f,
			0.f, 1.f, 0.f, 0.f,
			0.f, 0.f, 1.f, 0.f,
			-m_eye.x, -m_eye.y, -m_eye.z, 1.f
	};
	return glm::inverse(theMat);
}

glm::mat4 Camera::getModelViewMatrix() {
	vec3 w = normalize(-m_look);
	vec3 u = normalize(cross(m_up, w));
	vec3 v = normalize(cross(w, u));

	return
		mat4{
			u.x, v.x, w.x, 0.f,
			u.y, v.y, w.y, 0.f,
			u.z, v.z, w.z, 0.f,
			0.f, 0.f, 0.f, 1.f
		} *
		mat4{
			1.f, 0.f, 0.f, 0.f,
			0.f, 1.f, 0.f, 0.f,
			0.f, 0.f, 1.f, 0.f,
			-m_eye.x, -m_eye.y, -m_eye.z, 1.f
		};
}

void Camera::rotateV(float degrees) {
	vec3 w = normalize(-m_look);
	vec3 u = normalize(cross(m_up, w));
	vec3 v = normalize(cross(w, u));
	rotate(m_eye, v, degrees);
}

void Camera::rotateU(float degrees) {
	vec3 w = normalize(-m_look);
	vec3 u = normalize(cross(m_up, w));
	vec3 v = normalize(cross(w, u));
	rotate(m_eye, u, degrees);
}

void Camera::rotateW(float degrees) {
	vec3 w = normalize(-m_look);
	vec3 u = normalize(cross(m_up, w));
	vec3 v = normalize(cross(w, u));
	rotate(m_eye, w, -degrees);
}

void Camera::rotate(glm::vec3 point, glm::vec3 axis, float degree)
{
	mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(degree), axis);

	m_look = normalize(vec3(rotationMatrix * vec4(m_look, 1.0f)));
	m_up = normalize(vec3(rotationMatrix * vec4(m_up, 1.0f)));
}

void Camera::translate(glm::vec3 v) {
	m_eye += v;
}

glm::vec3 Camera::getEyePoint() {
	return m_eye;
}

glm::vec3 Camera::getLookVector() {
	return m_look;
}

glm::vec3 Camera::getUpVector() {
	return m_up;
}

float Camera::getViewAngle() {
	return viewAngle;
}

float Camera::getNearPlane() {
	return nearPlane;
}

float Camera::getFarPlane() {
	return farPlane;
}

int Camera::getScreenWidth() {
	return screenWidth;
}

int Camera::getScreenHeight() {
	return screenHeight;
}

float Camera::getScreenWidthRatio() {
	return screenWidthRatio;
}

