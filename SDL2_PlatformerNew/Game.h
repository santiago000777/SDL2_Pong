#pragma once
#include "Player.h"
#include "Ball.h"
#include "Background.h"
#include "Wall.h"
#include "Renderer.h"
#include "Brick.h"


#define FPS		160

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
	template<> void AddObject<Wall>(SDL_Rect dstBox, const std::string& path, SDL_Rect fromBox) {
		auto wall = new Wall(dstBox, path, fromBox, windowRect);
		
		walls.push_back(wall);
	}
	template<> void AddObject<Player>(SDL_Rect dstBox, const std::string& path, SDL_Rect fromBox) {
		auto player = new Player(dstBox, path, fromBox, windowRect);
		
		players.push_back(player);
	}
	template<> void AddObject<Ball>(SDL_Rect dstBox, const std::string& path, SDL_Rect fromBox) {
		auto ball = new Ball(dstBox, path, fromBox, windowRect);
		
		balls.push_back(ball);
	}

	void SetBackground(const std::string& BGpath);
	bool IsGameOver();
private:
	SDL_Window* window;
	SDL_Rect windowRect;
	Background* background;

	std::vector<Wall*> walls;
	std::vector<Ball*> balls;
	std::vector<Player*> players;
	std::vector<Brick*> bricks;

	const float deltaTime = 1000.0f / FPS;
	const float updateDelta = 1000.0f / 9000;
	std::chrono::time_point<std::chrono::high_resolution_clock> firstFrame, secondFrame, firstUpdate, secondUpdate;
	std::chrono::milliseconds durationFrame, durationUpdate;

	bool isGameOver = false;

	void Render();
	void Update(float delta);
};
