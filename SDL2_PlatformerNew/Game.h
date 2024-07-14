#pragma once
#include "Player.h"
#include "Background.h"
#include "Object.h"
#define FPS		60

class Game {
public:
	Game(const std::string& windowName = "Window", int posX = SDL_WINDOWPOS_CENTERED,
		 int posY = SDL_WINDOWPOS_CENTERED, int windowWidth = 800, int windowHeight = 600, int flags = SDL_WINDOW_SHOWN);
	Game(const Game& rhs) = delete;
	Game(Game&& rhs) = delete;
	~Game();

	void operator=(const Game& rhs) = delete;
	void operator=(Game&& rhs) = delete;

	void Loop();

	template <typename T> void AddObject(SDL_Rect dstBox, const std::string& path, SDL_Rect fromBox);
	template<> void AddObject<Object>(SDL_Rect dstBox, const std::string& path, SDL_Rect fromBox) {
		auto object = new Object(renderer, dstBox, path, fromBox, windowRect);
		objects.push_back(object);
	}
	template<> void AddObject<Player>(SDL_Rect dstBox, const std::string& path, SDL_Rect fromBox) {
		auto player = new Player(renderer, dstBox, path, fromBox, windowRect);
		objects.push_back(player);
	}

	void SetBackground(const std::string& BGpath);

private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Rect windowRect;
	Background* background;

	std::vector<Object*> objects;

	const float deltaTime = 1000.0f / FPS;
	const float updateDelta = 1000.0f / 9000;
	std::chrono::time_point<std::chrono::high_resolution_clock> firstFrame, secondFrame, firstUpdate, secondUpdate;
	std::chrono::milliseconds durationFrame, durationUpdate;

	void Render();
	void Clear();
	void Update(float delta);
};
