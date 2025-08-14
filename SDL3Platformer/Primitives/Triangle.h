#pragma once

#include "../Header/struct.h"

struct Triangle {

	// �ﰢ���� �����ϴ� �� ���� ����
	Vertex v1; // ù ��° ����
	Vertex v2; // �� ��° ����
	Vertex v3; // �� ��° ����

	// ������: �� ���� ������ �޾Ƽ� �ﰢ���� �ʱ�ȭ
	Triangle(const Vertex& vertex1, const Vertex& vertex2, const Vertex& vertex3)
		: v1(vertex1), v2(vertex2), v3(vertex3) {
	}

};