#pragma once

#include "../Header/struct.h"

struct Triangle {

	// 삼각형을 구성하는 세 개의 정점
	Vertex v1; // 첫 번째 정점
	Vertex v2; // 두 번째 정점
	Vertex v3; // 세 번째 정점

	// 생성자: 세 개의 정점을 받아서 삼각형을 초기화
	Triangle(const Vertex& vertex1, const Vertex& vertex2, const Vertex& vertex3)
		: v1(vertex1), v2(vertex2), v3(vertex3) {
	}

};