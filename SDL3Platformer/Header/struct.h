#pragma once
#include "Math.h"

struct Vertex
{
	Vec4 Position;
	Vec4 Color;
	Vec3 Normal;
	Vec2 TexCoords;

	// 생성자: 모든 멤버 변수를 초기화
	Vertex(const Vec4& position, const Vec4& color, 
		   const Vec3& normal, const Vec2& texCoords)
		: Position(position), Color(color), Normal(normal), TexCoords(texCoords) {
	}

};