#pragma once
#include "Math.h"

struct Vertex
{
	Vec4 Position;
	Vec4 Color;
	Vec3 Normal;
	Vec2 TexCoords;

	// ������: ��� ��� ������ �ʱ�ȭ
	Vertex(const Vec4& position, const Vec4& color, 
		   const Vec3& normal, const Vec2& texCoords)
		: Position(position), Color(color), Normal(normal), TexCoords(texCoords) {
	}

};