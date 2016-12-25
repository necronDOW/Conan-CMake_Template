#ifndef camera_h_defined
#define camera_h_defined

#include <GL/glew.h>
#include <SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "glProgram.h"
#include "glContext.h"

class Camera
{
	public:
		Camera() { }
		Camera(glm::vec3 position, glm::vec3 rotation, glProgram* program, float fovy, float aspect, float near, float far);

		void Translate(glm::vec3 translation);
		void Rotate(glm::vec3 rotation);
		void SetPosition(glm::vec3 newPosition);
		void SetRotation(glm::vec3 newRotation);
		void HandleInput(SDL_Event event, glContext& context);
		void Update();

		glm::mat4 GetProjection();
		glm::mat4 GetView();
		GLint GetProjectionLocation();
		GLint GetViewLocation();

	private:
		void ScrollZoom(float amount, glContext& context);

		glm::mat4 _projectionMatrix;
		glm::mat4 _viewMatrix;
		GLint _svlProjection;
		GLint _svlView;

		glm::vec3 _position;
		glm::vec3 _rotation;
		glm::vec3 _translation;
};

#endif