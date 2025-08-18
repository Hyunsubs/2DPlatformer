#include <pch.h>
#include "../Header/SDLCreate.h"
#include "../Primitives/Triangle.h"
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
	SDLManager& Sdl = SDLManager::Instance();
	if (!Sdl.Init()) return -1;

	SDL_Window* Window = Sdl.GetWindow();
	SDL_GLContext Context = Sdl.GetContext();

    Triangle Tri = Triangle(
        Vertex(glm::vec4(0.0f, 0.5f, 0.0f, 1.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.5f, 1.0f)),
        Vertex(glm::vec4(-0.5f, -0.5f, 0.0f, 1.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.5f)),
        Vertex(glm::vec4(0.5f, -0.5f, 0.0f, 1.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.5f))
	);


    std::string VertexShaderSource = LoadTextFile("Shader\\DefaultVertexShader.glsl");
    std::string FragmentShaderSource = LoadTextFile("Shader\\DefaultPixelShader.glsl");

    if (VertexShaderSource.empty() || FragmentShaderSource.empty()) {
        std::fprintf(stderr, "[ERR] Missing shader files. Set 'Copy to Output Directory'!\n");
        SDL_GL_DestroyContext(Context); SDL_DestroyWindow(Window); SDL_Quit(); return 1;
    }

    GLuint vs = CompileShader(GL_VERTEX_SHADER, VertexShaderSource.c_str(), "triangle.vert");
    GLuint fs = CompileShader(GL_FRAGMENT_SHADER, FragmentShaderSource.c_str(), "triangle.frag");
    if (!vs || !fs) {
        SDL_GL_DestroyContext(Context); SDL_DestroyWindow(Window); SDL_Quit(); return 1;
    }
    GLuint prog = LinkProgram(vs, fs);
    glDeleteShader(vs); glDeleteShader(fs);
    if (!prog) {
        SDL_GL_DestroyContext(Context); SDL_DestroyWindow(Window); SDL_Quit(); return 1;
    }

    float vertices[] = {
        // Position (x,y,z,w)    // Color (r,g,b,a)
        Tri.v1.Position.x, Tri.v1.Position.y, Tri.v1.Position.z, Tri.v1.Position.w,
        Tri.v1.Color.x,    Tri.v1.Color.y,    Tri.v1.Color.z,    Tri.v1.Color.w,

        Tri.v2.Position.x, Tri.v2.Position.y, Tri.v2.Position.z, Tri.v2.Position.w,
        Tri.v2.Color.x,    Tri.v2.Color.y,    Tri.v2.Color.z,    Tri.v2.Color.w,

        Tri.v3.Position.x, Tri.v3.Position.y, Tri.v3.Position.z, Tri.v3.Position.w,
        Tri.v3.Color.x,    Tri.v3.Color.y,    Tri.v3.Color.z,    Tri.v3.Color.w,
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
                event.window.windowID == SDL_GetWindowID(Window)) {
                running = false;
            }
        }

        // 뷰포트 설정
        int px = 0, py = 0;
        SDL_GetWindowSizeInPixels(Window, &px, &py);
        glViewport(0, 0, px, py);

        // 화면 클리어
        glClearColor(0.08f, 0.08f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// 셰이더 프로그램 사용
        glUseProgram(prog);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // 스왑 버퍼
		SDL_GL_SwapWindow(Window);
	}

	// 리소스 정리
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
    glDeleteProgram(prog);
	Sdl.Destroy();

	return 0;
}

