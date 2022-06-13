#pragma once

#include <GLM/glm.hpp>
#include <GLM/ext.hpp>

#include "Window.hpp"


class Camera
{
	void _updateVectors();

public:
	glm::vec3 right; // ������ ����������� ������
	glm::vec3 up; // ������ ����������� �����
	glm::vec3 front; // ������ ����������� ������

	glm::vec3 position;
	float fieldOfViewY; // ���� ������
	glm::mat4 rotation;

	Camera(glm::vec3 position, float fieldOfViewY);

	glm::mat4 GetProjectionMatrix();
	glm::mat4 GetViewMatrix();

	void FirstPersonViewRotate(float x, float y, float z);
};