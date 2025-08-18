#pragma once
#include "../Header/struct.h"

static unsigned int nextID = 0; // ���� ID�� ���� ���� ����

class GameObject
{
public:
	GameObject();
	~GameObject();

private:
	unsigned int ID; // ��ü�� ���� ID
	Transform Trans; // ��ü�� ��ȯ ���� (��ġ, ȸ��, ũ�� ��)


public:
	unsigned int GetID() const { return ID; }

	glm::vec3 GetPosition() const { return Trans.Position; }
	void SetPosition(const glm::vec3& position) { Trans.Position = position; }

	glm::vec3 GetRotation() const { return Trans.Rotation; }
	void SetRotation(const glm::vec3& rotation) { Trans.Rotation = rotation; }

	glm::vec3 GetScale() const { return Trans.Scale; }
	void SetScale(const glm::vec3& scale) { Trans.Scale = scale; }

	glm::mat4 GetTransformMatrix() const { return Trans.GetMatrix(); }
	void SetTransform(const Transform& transform) { Trans = transform; }
};

