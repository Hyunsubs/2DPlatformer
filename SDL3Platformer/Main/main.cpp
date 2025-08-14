#include <glad/glad.h>
#include <iostream>
#include "../Header/External.h"
#include "../Header/Math.h"

using namespace std;

bool SetGLAttributes();

int main()
{
	// SDL 초기화
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL 초기화 실패: %s", SDL_GetError());
        return 1; // 적절한 오류 처리 또는 종료
    }

    if (!SetGLAttributes())
    {
        cout << "OpenGL 초기화 실패" << endl;
    }

	// SDL 창 생성
    SDL_Window* window = SDL_CreateWindow("OpenGL Projects", 1366, 768, SDL_WINDOW_MINIMIZED | SDL_WINDOW_MAXIMIZED |
      SDL_WINDOW_OPENGL);

    if (!window) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateWindow 실패: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    
	// OpenGL 컨텍스트 생성
    SDL_GLContext context = SDL_GL_CreateContext(window);
    if (!context) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "OpenGL 컨텍스트 생성 실패: %s", SDL_GetError());
        SDL_Quit();
        return 1; 
	}

	// OpenGL 확장 로딩
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "GLAD 로드 실패");
        SDL_GL_DestroyContext(context);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

	// OpenGL 버전 출력
    int major, minor;
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);
	cout << "OpenGL 버전: " << major << "." << minor << endl;

	// Adaptive VSync 설정
    if (SDL_GL_SetSwapInterval(-1) != 0) {
		SDL_GL_SetSwapInterval(1); // 실패 시 일반 VSync 설정
	}

	bool running = true;
	SDL_Event event;

    // 기본 렌더 상태
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_FRAMEBUFFER_SRGB);

    while (running) {
        // 이벤트 처리
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) running = false;
            if (event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED &&
                event.window.windowID == SDL_GetWindowID(window)) {
                running = false;
            }
        }

        // 뷰포트 설정
        int px = 0, py = 0;
        SDL_GetWindowSizeInPixels(window, &px, &py);
        glViewport(0, 0, px, py);

        // 화면 클리어
        glClearColor(0.08f, 0.08f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // 스왑 버퍼
		SDL_GL_SwapWindow(window);
	}

    // 리소스 정리
	SDL_GL_DestroyContext(context);
    SDL_DestroyWindow(window);
	SDL_Quit();


	return 0;
}

bool SetGLAttributes() {
    // OpenGL 초기화 코드 작성
    // 예: glewInit(), OpenGL 컨텍스트 설정 등
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_FRAMEBUFFER_SRGB_CAPABLE, 1);

    return true; // 성공적으로 초기화되면 true 반환
}