#include "Camera.hpp"


void Camera::_updateVectors()
{
	// умножаем матрицу вращения на направляющие вектора
	right = glm::vec3(rotation * glm::vec4(1, 0, 0, -1));
	up = glm::vec3(rotation * glm::vec4(0, 1, 0, -1));
	front = glm::vec3(rotation * glm::vec4(0, 0, -1, -1)); // -1 потому что Oz направлена в сторону экрана
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
	// вычисляем соотношение сторон окна, чтобы при изменения размеров окна изображение не сплющивалось
	const float aspectRatio = static_cast<float>(Window::width) / static_cast<float>(Window::height);

	// создаем матрицу проекции перспективы 4x4 для преобразования точек
	return glm::perspective(
		fieldOfViewY,	// угол обзора по Y
		aspectRatio,	// соотношение сторон окна
		0.1f,			// ближняя плоскость фрустума (усеченной пирамиды)
		100.0f			// дальняя плоскость фрустума
	);
}

void Camera::FirstPersonViewRotate(float x, float y, float z)
{
	// порядок вращения для вида от первого лица
	rotation = glm::rotate(rotation, z, glm::vec3(0, 0, 1));
	rotation = glm::rotate(rotation, y, glm::vec3(0, 1, 0));
	rotation = glm::rotate(rotation, x, glm::vec3(1, 0, 0));

	_updateVectors();
}

glm::mat4 Camera::GetViewMatrix()
{
	// возвращаем матрицу вида – то, куда смотрит камера
	return glm::lookAt(
		position,			// позиция камеры	
		position + front,	// позиция точки, на которую смотрит камера
		up					// вверх камеры	
	);
}
