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
    // SDL 초기화
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL 초기화 실패: %s", SDL_GetError());
        return false;
    }

    if (!SetGLAttributes())
    {
        cout << "OpenGL 초기화 실패" << endl;
        return false;
    }

    // SDL 창 생성
    window = SDL_CreateWindow("OpenGL Projects", 1366, 768, SDL_WINDOW_MINIMIZED | SDL_WINDOW_MAXIMIZED |
        SDL_WINDOW_OPENGL);

    if (!window) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateWindow 실패: %s", SDL_GetError());
        SDL_Quit();
        return false;
    }

    // OpenGL 컨텍스트 생성
    context = SDL_GL_CreateContext(window);
    if (!context) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "OpenGL 컨텍스트 생성 실패: %s", SDL_GetError());
        SDL_Quit();
        return false;
    }

    // OpenGL 확장 로딩
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "GLAD 로드 실패");
        SDL_GL_DestroyContext(context);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
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

    // 기본 렌더 상태
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_FRAMEBUFFER_SRGB);

    return true;
}

void SDLManager::Destroy()
{
    // OpenGL 컨텍스트와 SDL 창을 정리
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

SDL_Window* SDLManager::GetWindow() const { return window; }
SDL_GLContext SDLManager::GetContext() const { return context; }
