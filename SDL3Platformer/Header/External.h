#pragma once
#include <SDL3/SDL.h>

// SDL ���̺귯�� ��ũ ����� ��忡 ���� �ٸ��� ����
#ifdef _DEBUG
#pragma comment(lib, "../lib/Debug/SDL3.lib")
#else
#pragma comment(lib, "../lib/Release/SDL3.lib")
#endif
