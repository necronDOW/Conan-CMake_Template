#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 rotation, glProgram* program, float fovy, float aspect, float near, float far)
{
	_position = position;
	_rotation = rotation;
	_svlProjection = program->GetShaderVarLocation("projectionMatrix", glProgram::Uni);
	_svlView = program->GetShaderVarLocation("viewMatrix", glProgram::Uni);

	_projectionMatrix = glm::perspective(fovy, aspect, near, far);
}

void Camera::Translate(glm::vec3 translation)
{
	_position += translation;

	if (_position.z > -0.1f)
		_position.z = -0.1f;
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

void Camera::HandleInput(SDL_Event event, glContext& context)
{
	SDL_Keycode key = event.key.keysym.sym;

	switch (event.type)
	{
		case SDL_KEYDOWN:
			if (!event.key.repeat)
			{
				if (key == SDLK_w) _translation.y -= 0.01f;
				if (key == SDLK_a) _translation.x += 0.01f;
				if (key == SDLK_s) _translation.y += 0.01f;
				if (key == SDLK_d) _translation.x -= 0.01f;
			}

			if (key == SDLK_r) ScrollZoom(1.0f, context);
			if (key == SDLK_f) ScrollZoom(-1.0f, context);
			break;

		case SDL_KEYUP:
			if (key == SDLK_w || key == SDLK_s) _translation.y = 0.0f;
			if (key == SDLK_a || key == SDLK_d) _translation.x = 0.0f;
			break;

		case SDL_MOUSEWHEEL:
			ScrollZoom(event.wheel.y, context);
			break;
	}
}

void Camera::Update()
{
	Translate(_translation);

	_viewMatrix = glm::translate(glm::mat4(1.0f), _position);
	_viewMatrix = glm::rotate(_viewMatrix, glm::radians(_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	_viewMatrix = glm::rotate(_viewMatrix, glm::radians(_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	_viewMatrix = glm::rotate(_viewMatrix, glm::radians(_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
}

void Camera::ScrollZoom(float amount, glContext& context)
{
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	glm::vec2 mousePos = glm::vec2(mouseX - (context.GetDimensions().w / 2),
		mouseY - (context.GetDimensions().h / 2));

	Translate(glm::vec3(-mousePos.x * 0.0001f,
		mousePos.y * 0.0001f, amount * 0.1f));
}

glm::mat4 Camera::GetProjection() { return _projectionMatrix; }
glm::mat4 Camera::GetView() { return _viewMatrix; }
GLint Camera::GetProjectionLocation() { return _svlProjection; }
GLint Camera::GetViewLocation() { return _svlView; }