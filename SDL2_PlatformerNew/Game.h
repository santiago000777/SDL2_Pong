#pragma once
#include "Player.h"
#include "Ball.h"
#include "Background.h"
#include "Wall.h"
#include "Renderer.h"
#include "Brick.h"

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

	template <typename T> void AddObject(SDL_Rect dstBox, const std::string& path, int characterWidth);
	template<> void AddObject<Wall>(SDL_Rect dstBox, const std::string& path, int characterWidth) {
		auto wall = new Wall(dstBox, path, characterWidth, windowRect);
		
		walls.push_back(wall);
	}
	template<> void AddObject<Player>(SDL_Rect dstBox, const std::string& path, int characterWidth) {
		auto player = new Player(dstBox, path, characterWidth, windowRect);
		
		players.push_back(player);
	}
	template<> void AddObject<Ball>(SDL_Rect dstBox, const std::string& path, int characterWidth) {
		auto ball = new Ball(dstBox, path, characterWidth, windowRect);
		
		balls.push_back(ball);
	}
	template<> void AddObject<Brick>(SDL_Rect dstBox, const std::string& path, int characterWidth) {
		auto brick = new Brick(dstBox, path, characterWidth, windowRect);

		bricks.push_back(brick);
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
	std::chrono::time_point<std::chrono::high_resolution_clock> firstFrame, secondFrame, firstUpdate, secondUpdate;
	std::chrono::milliseconds durationFrame, durationUpdate;

	bool isGameOver = false;

	void Basket();
	void Render();
	void Update();
	void HandleEvents();
	void Collision();
};
