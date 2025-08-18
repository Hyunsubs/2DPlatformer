#pragma once
#include "../pch.h"

struct Vertex
{
	glm::vec4 Position;
	glm::vec4 Color;
	glm::vec3 Normal;
	glm::vec2 TexCoords;

	// 생성자: 모든 멤버 변수를 초기화
	Vertex(const glm::vec4& position, const glm::vec4& color, 
		   const glm::vec3& normal, const glm::vec2& texCoords)
		: Position(position), Color(color), Normal(normal), TexCoords(texCoords) {
	}

};


struct Transform
{
	glm::vec3 Position;
	glm::vec3 Rotation;
	glm::vec3 Scale;

	glm::mat4 GetMatrix() const {
		glm::mat4 translation = glm::translate(glm::mat4(1.0f), Position);
		glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(Rotation.x), glm::vec3(1, 0, 0)) *
						glm::rotate(glm::mat4(1.0f), glm::radians(Rotation.y), glm::vec3(0, 1, 0)) *
						glm::rotate(glm::mat4(1.0f), glm::radians(Rotation.z), glm::vec3(0, 0, 1));
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), Scale);
		return translation * rotation * scale;
	}
};