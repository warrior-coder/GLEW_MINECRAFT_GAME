#include "Camera.hpp"


void Camera::_updateVectors()
{
	// �������� ������� �������� �� ������������ �������
	right = glm::vec3(rotation * glm::vec4(1, 0, 0, -1));
	up = glm::vec3(rotation * glm::vec4(0, 1, 0, -1));
	front = glm::vec3(rotation * glm::vec4(0, 0, -1, -1)); // -1 ������ ��� Oz ���������� � ������� ������
}

Camera::Camera(glm::vec3 position, float fieldOfViewY)
	: position(position)
	, fieldOfViewY(fieldOfViewY)
	, rotation(1.0f)
{
	_updateVectors();
}

glm::mat4 Camera::GetProjectionMatrix()
{
	// ��������� ����������� ������ ����, ����� ��� ��������� �������� ���� ����������� �� ������������
	const float aspectRatio = static_cast<float>(Window::width) / static_cast<float>(Window::height);

	// ������� ������� �������� ����������� 4x4 ��� �������������� �����
	return glm::perspective(
		fieldOfViewY,	// ���� ������ �� Y
		aspectRatio,	// ����������� ������ ����
		0.1f,			// ������� ��������� �������� (��������� ��������)
		100.0f			// ������� ��������� ��������
	);
}

void Camera::FirstPersonViewRotate(float x, float y, float z)
{
	// ������� �������� ��� ���� �� ������� ����
	rotation = glm::rotate(rotation, z, glm::vec3(0, 0, 1));
	rotation = glm::rotate(rotation, y, glm::vec3(0, 1, 0));
	rotation = glm::rotate(rotation, x, glm::vec3(1, 0, 0));

	_updateVectors();
}

glm::mat4 Camera::GetViewMatrix()
{
	// ���������� ������� ���� � ��, ���� ������� ������
	return glm::lookAt(
		position,			// ������� ������	
		position + front,	// ������� �����, �� ������� ������� ������
		up					// ����� ������	
	);
}
