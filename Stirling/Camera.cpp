/*! \file Camera.cpp
	\brief Camera, View, and Projection matrix wrapper class
*/

#include "Camera.h"

Camera::Camera(float _fov, float _aspect, float _near, float _far) {
	fov = _fov;
	aspect = _aspect;
	near = _near;
	far = _far;

	edit = true;

	position = glm::vec3(0.0f);
	rotMatrix = glm::mat4(1.0f);

	updateProjection();
	updateView();
}

void Camera::update() {
	updateView();
	updateProjection();
}

void Camera::updateView() {
	view = rotMatrix;
	view = glm::translate(view, position);
	edit = true;
}

void Camera::updateProjection() {
	projection = glm::perspective(fov, aspect, near, far);
	edit = true;
}

void Camera::setCameraPosition(glm::vec3 pos) {
	position = pos;
	updateView();
}

void Camera::translateCamera(glm::vec3 trans) {
	position += trans;
	updateView();
}

void Camera::setCameraRotation(float angle, glm::vec3 axis) {
	rotMatrix = glm::rotate(glm::mat4(1.0f), angle, axis);
	updateView();
}

void Camera::rotateCamera(float angle, glm::vec3 axis) {
	glm::mat4 _rotMatrix = glm::mat4(1.0f);
	_rotMatrix = glm::rotate(_rotMatrix, angle, axis);
	rotMatrix *= _rotMatrix;
	updateView();
}