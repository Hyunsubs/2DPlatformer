#include "pch.h"
#include "GameObject.h"

unsigned int nextID = 0; // 다음 ID를 위한 정적 변수

GameObject::GameObject()
	: ID(nextID++)
	, Transform()
{

}

GameObject::~GameObject()
{
}
