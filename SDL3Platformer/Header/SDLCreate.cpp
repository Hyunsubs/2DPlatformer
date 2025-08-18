#include <pch.h>
#include "SDLCreate.h"


using namespace std;

SDLManager::SDLManager() : window(nullptr), context(nullptr) 
{

}

SDLManager::~SDLManager() 
{
    Destroy();
}

SDLManager& SDLManager::Instance()
{
    static SDLManager instance;
    return instance;
}

bool SDLManager::Init()
{
    // SDL �ʱ�ȭ
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL �ʱ�ȭ ����: %s", SDL_GetError());
        return false;
    }

    if (!SetGLAttributes())
    {
        cout << "OpenGL �ʱ�ȭ ����" << endl;
        return false;
    }

    // SDL â ����
    window = SDL_CreateWindow("OpenGL Projects", 1366, 768, SDL_WINDOW_MINIMIZED | SDL_WINDOW_MAXIMIZED |
        SDL_WINDOW_OPENGL);

    if (!window) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateWindow ����: %s", SDL_GetError());
        SDL_Quit();
        return false;
    }

    // OpenGL ���ؽ�Ʈ ����
    context = SDL_GL_CreateContext(window);
    if (!context) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "OpenGL ���ؽ�Ʈ ���� ����: %s", SDL_GetError());
        SDL_Quit();
        return false;
    }

    // OpenGL Ȯ�� �ε�
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "GLAD �ε� ����");
        SDL_GL_DestroyContext(context);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
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

    // �⺻ ���� ����
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_FRAMEBUFFER_SRGB);

    return true;
}

void SDLManager::Destroy()
{
    // OpenGL ���ؽ�Ʈ�� SDL â�� ����
    if (context) {
        SDL_GL_DestroyContext(context);
        context = nullptr;
    }
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    SDL_Quit();
}

bool SDLManager::SetGLAttributes()
{
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

SDL_Window* SDLManager::GetWindow() const { return window; }
SDL_GLContext SDLManager::GetContext() const { return context; }
