#pragma once
#include "Player.h"
#include "Ball.h"
#include "Background.h"
#include "Wall.h"
#include "Renderer.h"
#include "Brick.h"
#include "Bubble.h"

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
		auto wall = new Wall(dstBox, path, characterWidth);
		
		walls.push_back(wall);
	}
	template<> void AddObject<Player>(SDL_Rect dstBox, const std::string& path, int characterWidth) {
		auto player = new Player(dstBox, path, characterWidth);
		
		players.push_back(player);
	}
	template<> void AddObject<Ball>(SDL_Rect dstBox, const std::string& path, int characterWidth) {
		auto ball = new Ball(dstBox, path, characterWidth);
		
		balls.push_back(ball);
	}
	template<> void AddObject<Brick>(SDL_Rect dstBox, const std::string& path, int characterWidth) {
		auto brick = new Brick(dstBox, path, characterWidth);

		bricks.push_back(brick);
	}
	template<> void AddObject<Bubble>(SDL_Rect dstBox, const std::string& path, int characterWidth) {
		auto bubble = new Bubble(dstBox, path, characterWidth);

		bubbles.push_back(bubble);
	}


	void SetBackground(const std::string& BGpath);

	int GetCountOfBricks() const;

	bool IsEnd();
private:
	SDL_Window* window;
	Background* background;

	std::vector<Wall*> walls;
	std::vector<Ball*> balls;
	std::vector<Player*> players;
	std::vector<Brick*> bricks;
	std::vector<Bubble*> bubbles;

	const float deltaTime = 1000.0f / FPS;
	std::chrono::time_point<std::chrono::high_resolution_clock> firstFrame, secondFrame, firstUpdate, secondUpdate;
	std::chrono::milliseconds durationFrame, durationUpdate;

	SDL_Rect gameOverRect { 0, 800, 600, 20 };

	bool isEnd = false;

	void Basket();
	void Render();
	void Update();
	void HandleEvents();
	void Collision();
};
