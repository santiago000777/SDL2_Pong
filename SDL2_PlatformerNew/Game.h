#pragma once
#include "Object.h"
#define FPS		60

class Game {
public:
	Game(const std::string& windowName, int posX, int posY, int windowWidth, int windowHeight, int flags);
	Game(const Game& rhs) = delete;
	Game(Game&& rhs) = delete;
	~Game();

	void operator=(const Game& rhs) = delete;
	void operator=(Game&& rhs) = delete;

	void Loop();

	template <typename T>
	void AddObject();

	void SetBackGround(const std::string& BGpath);

private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Rect windowRect;
	BackGround* backGround;

	std::vector<Object*> objects;

	const float deltaTime = 1000.0f / FPS;
	const float posunPeriod = 1000.0f / 9000;
	std::chrono::time_point<std::chrono::high_resolution_clock> firstFrame, secondFrame, firstPosun, secondPosun;
	std::chrono::milliseconds durationFrame, durationPosun;

	void InitWindow(const std::string& windowName = "Window", int posX = SDL_WINDOWPOS_CENTERED, 
					int posY = SDL_WINDOWPOS_CENTERED, int windowWidth = 800, int windowHeight = 600, int flags = SDL_WINDOW_SHOWN);

	void InitRenderer(SDL_Window* window, int index = -1, int flags = 1);

	void Render();
	void Clear();
	void Posun(float delta);
};

