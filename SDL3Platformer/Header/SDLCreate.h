#pragma once
#include <glad/glad.h>
#include "../Header/External.h"
#include <SDL3/SDL.h>

class SDLManager
{
public:
    static SDLManager& Instance();

    bool Init();
    void Destroy();

    SDL_Window* GetWindow() const;
    SDL_GLContext GetContext() const;

private:
    SDLManager();
    ~SDLManager();
    SDLManager(const SDLManager&) = delete;
    SDLManager& operator=(const SDLManager&) = delete;
	bool SetGLAttributes();

    SDL_Window* window;
    SDL_GLContext context;
};