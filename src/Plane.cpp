//#include "Plane.h"
//
//Plane::Plane(glProgram* program, glm::vec3 position, glm::vec3 size, int xCellCount, int yCellCount)
//	: DrawableBase(program, position)
//{
//
//}
//
//void Plane::InitializeVertexBuffer()
//{
//	DrawableBase::InitializeVertexBuffer();
//
//	DebugTools::Log("Generating element buffer ...", DebugTools::Info, 1);
//	glGenBuffers(1, &_oElementBuffer);
//	DebugTools::Log("Element Buffer created! GLuint is: " + _oElementBuffer, DebugTools::Info, 2);
//
//	DebugTools::Log("Creating element buffer data ...", DebugTools::Info, 1);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _oElementBuffer);
//		glBufferData(GL_ELEMENT_ARRAY_BUFFER, _eData.size() * sizeof(_eData.front()), &_eData.front(), GL_STATIC_DRAW);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//
//	InitializeVertexArrayObject();
//}
//
//void Plane::Draw()
//{
//	DrawableBase::PerformDraw(GL_TRIANGLES, 3);
//}