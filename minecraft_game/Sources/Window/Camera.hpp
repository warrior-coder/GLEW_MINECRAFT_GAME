#pragma once

#include <GLM/glm.hpp>
#include <GLM/ext.hpp>

#include "Window.hpp"


class Camera
{
	void _updateVectors();

public:
	glm::vec3 right; // вектор направления вправо
	glm::vec3 up; // вектор направления вверх
	glm::vec3 front; // вектор направления вперед

	glm::vec3 position;
	float fieldOfViewY; // угол обзора
	glm::mat4 rotation;

	Camera(glm::vec3 position, float fieldOfViewY);

	glm::mat4 GetProjectionMatrix();
	glm::mat4 GetViewMatrix();

	void FirstPersonViewRotate(float x, float y, float z);
};