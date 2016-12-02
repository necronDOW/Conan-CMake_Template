#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 rotation, glProgram* program, float fovy, float aspect, float near, float far)
{
	_position = position;
	_rotation = rotation;
	_projectionLocation = program->GetShaderVarLocation("projectionMatrix", glProgram::Uni);
	_viewLocation = program->GetShaderVarLocation("viewMatrix", glProgram::Uni);

	_projectionMatrix = glm::perspective(fovy, aspect, near, far);
}

void Camera::Translate(glm::vec3 translation)
{
	_position += translation;
}

void Camera::Rotate(glm::vec3 rotation)
{
	_rotation += rotation;
}

void Camera::SetPosition(glm::vec3 newPosition)
{
	_position = newPosition;
}

void Camera::SetRotation(glm::vec3 newRotation)
{
	_rotation = newRotation;
}

void Camera::HandleInput(SDL_Event event, SDL_Keycode key)
{

}

void Camera::Update()
{
	_viewMatrix = glm::translate(glm::mat4(1.0f), _position);
	_viewMatrix = glm::rotate(_viewMatrix, glm::radians(_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	_viewMatrix = glm::rotate(_viewMatrix, glm::radians(_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	_viewMatrix = glm::rotate(_viewMatrix, glm::radians(_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
}

glm::mat4 Camera::GetProjection() { return _projectionMatrix; }
glm::mat4 Camera::GetView() { return _viewMatrix; }
GLint Camera::GetProjectionLocation() { return _projectionLocation; }
GLint Camera::GetViewLocation() { return _viewLocation; }