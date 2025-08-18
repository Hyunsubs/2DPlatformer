#pragma once
#include <SDL3/SDL.h>

// SDL 라이브러리 링크 디버그 모드에 따라 다르게 설정
#ifdef _DEBUG
#pragma comment(lib, "../lib/Debug/SDL3.lib")
#else
#pragma comment(lib, "../lib/Release/SDL3.lib")
#endif
