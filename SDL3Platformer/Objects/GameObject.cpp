#include "pch.h"
#include "GameObject.h"

unsigned int nextID = 0; // ���� ID�� ���� ���� ����

GameObject::GameObject()
	: ID(nextID++)
	, Transform()
{

}

GameObject::~GameObject()
{
}
