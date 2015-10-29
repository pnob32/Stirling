/*! \file Camera.h
\brief Wrapper for the View matrix

This class is used to customize and initialize the view matrix, as well as translate and rotate the camera, lookat, ect
*/

#ifndef CAMERA_H
#define CAMERA_H

#include "global_includes.h"

class Camera
{
public:
	Camera() {}
	Camera(float _fov, float _aspect, float _near, float _far);

	void update();

	void setCameraPosition(glm::vec3 pos);
	void translateCamera(glm::vec3 trans);
	void setCameraRotation(float angle, glm::vec3 axis);
	void rotateCamera(float angle, glm::vec3 axis);

	inline glm::mat4 getProjectionMatrix() { return projection; }
	inline glm::mat4 getViewMatrix() { return view; }

	inline bool edited() { return edit; }
	inline void upToDate() { edit = false; }

private:
	float fov, aspect, near, far;

	bool edit;

	glm::vec3 position;
	glm::mat4 rotMatrix;

	glm::mat4 projection;
	glm::mat4 view;

	void updateView();
	void updateProjection();
};

#endif