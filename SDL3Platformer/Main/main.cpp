#include <glad/glad.h>
#include <iostream>
#include "../Header/External.h"
#include "../Header/Math.h"

using namespace std;

bool SetGLAttributes();

int main()
{
	// SDL �ʱ�ȭ
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL �ʱ�ȭ ����: %s", SDL_GetError());
        return 1; // ������ ���� ó�� �Ǵ� ����
    }

    if (!SetGLAttributes())
    {
        cout << "OpenGL �ʱ�ȭ ����" << endl;
    }

	// SDL â ����
    SDL_Window* window = SDL_CreateWindow("OpenGL Projects", 1366, 768, SDL_WINDOW_MINIMIZED | SDL_WINDOW_MAXIMIZED |
      SDL_WINDOW_OPENGL);

    if (!window) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateWindow ����: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    
	// OpenGL ���ؽ�Ʈ ����
    SDL_GLContext context = SDL_GL_CreateContext(window);
    if (!context) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "OpenGL ���ؽ�Ʈ ���� ����: %s", SDL_GetError());
        SDL_Quit();
        return 1; 
	}

	// OpenGL Ȯ�� �ε�
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "GLAD �ε� ����");
        SDL_GL_DestroyContext(context);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

	// OpenGL ���� ���
    int major, minor;
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);
	cout << "OpenGL ����: " << major << "." << minor << endl;

	// Adaptive VSync ����
    if (SDL_GL_SetSwapInterval(-1) != 0) {
		SDL_GL_SetSwapInterval(1); // ���� �� �Ϲ� VSync ����
	}

	bool running = true;
	SDL_Event event;

    // �⺻ ���� ����
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_FRAMEBUFFER_SRGB);

    while (running) {
        // �̺�Ʈ ó��
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) running = false;
            if (event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED &&
                event.window.windowID == SDL_GetWindowID(window)) {
                running = false;
            }
        }

        // ����Ʈ ����
        int px = 0, py = 0;
        SDL_GetWindowSizeInPixels(window, &px, &py);
        glViewport(0, 0, px, py);

        // ȭ�� Ŭ����
        glClearColor(0.08f, 0.08f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // ���� ����
		SDL_GL_SwapWindow(window);
	}

    // ���ҽ� ����
	SDL_GL_DestroyContext(context);
    SDL_DestroyWindow(window);
	SDL_Quit();


	return 0;
}

bool SetGLAttributes() {
    // OpenGL �ʱ�ȭ �ڵ� �ۼ�
    // ��: glewInit(), OpenGL ���ؽ�Ʈ ���� ��
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_FRAMEBUFFER_SRGB_CAPABLE, 1);

    return true; // ���������� �ʱ�ȭ�Ǹ� true ��ȯ
}