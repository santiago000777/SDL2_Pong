#pragma once
#include "Player.h"
#include "Ball.h"
#include "Background.h"
#include "Object.h"
#include "Renderer.h"
#include "Brick.h"

#define FPS		60

#define FPS		165

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
		auto wall = new Object(dstBox, path, fromBox, windowRect);
		objects.push_back(wall);
		walls.push_back(wall);
	}
	template<> void AddObject<Player>(SDL_Rect dstBox, const std::string& path, SDL_Rect fromBox) {
		auto player = new Player(dstBox, path, fromBox, windowRect);
		objects.push_back(player);
		players.push_back(player);

		player->SetPlayers(&players);
	}
	template<> void AddObject<Ball>(SDL_Rect dstBox, const std::string& path, SDL_Rect fromBox) {
		auto ball = new Ball(dstBox, path, fromBox, windowRect);
		objects.push_back(ball);
		balls.push_back(ball);
	}
	template<> void AddObject<Brick>(SDL_Rect dstBox, const std::string& path, SDL_Rect fromBox) {
		auto brick = new Brick(dstBox, path, fromBox, windowRect);
		objects.push_back(brick);
		bricks.push_back(brick);
	}

	void SetBackground(const std::string& BGpath);
	bool IsGameOver();
private:
	SDL_Window* window;
	SDL_Rect windowRect;
	Background* background;

	std::vector<Object*> objects;

	std::vector<Object*> walls;
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
