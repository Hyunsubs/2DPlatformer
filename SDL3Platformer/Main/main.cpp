#include "../Header/SDLCreate.h"
#include "../Header/Math.h"
#include "../Primitives/Triangle.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <crtdbg.h>

// ---------- 유틸: 파일 읽기 ----------
static std::string LoadTextFile(const char* path) {
    std::ifstream ifs(path, std::ios::in | std::ios::binary);
    if (!ifs) {
        std::fprintf(stderr, "[ERR] Failed to open %s\n", path);
        return {};
    }
    std::ostringstream oss;
    oss << ifs.rdbuf();
    return oss.str();
}

// ---------- 유틸: 셰이더 컴파일/링크 ----------
static GLuint CompileShader(GLenum stage, const char* src, const char* debugName) {
    GLuint s = glCreateShader(stage);
    glShaderSource(s, 1, &src, nullptr);
    glCompileShader(s);
    GLint ok = GL_FALSE;
    glGetShaderiv(s, GL_COMPILE_STATUS, &ok);
    if (!ok) {
        GLint len = 0; glGetShaderiv(s, GL_INFO_LOG_LENGTH, &len);
        std::string log(len, '\0');
        glGetShaderInfoLog(s, len, nullptr, log.data());
        std::fprintf(stderr, "[SHADER] Compile failed (%s):\n%s\n", debugName, log.c_str());
        glDeleteShader(s);
        return 0;
    }
    return s;
}

static GLuint LinkProgram(GLuint vs, GLuint fs) {
    GLuint p = glCreateProgram();
    glAttachShader(p, vs);
    glAttachShader(p, fs);
    glLinkProgram(p);
    GLint ok = GL_FALSE; glGetProgramiv(p, GL_LINK_STATUS, &ok);
    if (!ok) {
        GLint len = 0; glGetProgramiv(p, GL_INFO_LOG_LENGTH, &len);
        std::string log(len, '\0');
        glGetProgramInfoLog(p, len, nullptr, log.data());
        std::fprintf(stderr, "[PROGRAM] Link failed:\n%s\n", log.c_str());
        glDeleteProgram(p);
        return 0;
    }
    glDetachShader(p, vs);
    glDetachShader(p, fs);
    return p;
}

int main()
{
	// 메모리 누수 검사
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	bool running = true;
	SDL_Event event;
	SDLManager& sdl = SDLManager::Instance();
	if (!sdl.Init()) return -1;

	SDL_Window* window = sdl.GetWindow();
	SDL_GLContext context = sdl.GetContext();

    Triangle tri = Triangle(
        Vertex(Vec4(0.0f, 0.5f, 0.0f, 1.0f), Vec4(1.0f, 0.0f, 0.0f, 1.0f), Vec3(0.0f, 0.0f, 1.0f), Vec2(0.5f, 1.0f)),
        Vertex(Vec4(-0.5f, -0.5f, 0.0f, 1.0f), Vec4(0.0f, 1.0f, 0.0f, 1.0f), Vec3(0.0f, 0.0f, 1.0f), Vec2(0.0f, 0.5f)),
        Vertex(Vec4(0.5f, -0.5f, 0.0f, 1.0f), Vec4(0.0f, 0.0f, 1.0f, 1.0f), Vec3(0.0f, 0.0f, 1.0f), Vec2(1.0f, 1.5f))
	);


    std::string vsSrc = LoadTextFile("Shader\\DefaultVertexShader.glsl");
    std::string fsSrc = LoadTextFile("Shader\\DefaultPixelShader.glsl");

    if (vsSrc.empty() || fsSrc.empty()) {
        std::fprintf(stderr, "[ERR] Missing shader files. Set 'Copy to Output Directory'!\n");
        SDL_GL_DestroyContext(context); SDL_DestroyWindow(window); SDL_Quit(); return 1;
    }

    GLuint vs = CompileShader(GL_VERTEX_SHADER, vsSrc.c_str(), "triangle.vert");
    GLuint fs = CompileShader(GL_FRAGMENT_SHADER, fsSrc.c_str(), "triangle.frag");
    if (!vs || !fs) {
        SDL_GL_DestroyContext(context); SDL_DestroyWindow(window); SDL_Quit(); return 1;
    }
    GLuint prog = LinkProgram(vs, fs);
    glDeleteShader(vs); glDeleteShader(fs);
    if (!prog) {
        SDL_GL_DestroyContext(context); SDL_DestroyWindow(window); SDL_Quit(); return 1;
    }

    float vertices[] = {
        // Position (x,y,z,w)    // Color (r,g,b,a)
        tri.v1.Position.x, tri.v1.Position.y, tri.v1.Position.z, tri.v1.Position.w,
        tri.v1.Color.x,    tri.v1.Color.y,    tri.v1.Color.z,    tri.v1.Color.w,

        tri.v2.Position.x, tri.v2.Position.y, tri.v2.Position.z, tri.v2.Position.w,
        tri.v2.Color.x,    tri.v2.Color.y,    tri.v2.Color.z,    tri.v2.Color.w,

        tri.v3.Position.x, tri.v3.Position.y, tri.v3.Position.z, tri.v3.Position.w,
        tri.v3.Color.x,    tri.v3.Color.y,    tri.v3.Color.z,    tri.v3.Color.w,
    };

    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Position
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Color
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(4 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


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

		// 셰이더 프로그램 사용
        glUseProgram(prog);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // 스왑 버퍼
		SDL_GL_SwapWindow(window);
	}

	// 리소스 정리
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
    glDeleteProgram(prog);
	sdl.Destroy();

	return 0;
}

