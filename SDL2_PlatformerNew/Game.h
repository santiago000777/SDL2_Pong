#pragma once
#include "IGame.h"
#include "Player.h"
#include "Ball.h"
#include "Background.h"
#include "Wall.h"
#include "IRenderer.h"
#include "Brick.h"
#include "Bubble.h"
#include "Bomb.h"

#define FPS		60

class SGame : public IGame {
public:
	SGame() {}
	SGame(const SGame& rhs) = delete;
	SGame(SGame&& rhs) = delete;
	~SGame();

	void operator=(const SGame& rhs) = delete;
	void operator=(SGame&& rhs) = delete;

	void Init(const std::string& windowName = "Window", int posX = SDL_WINDOWPOS_CENTERED,
					 int posY = SDL_WINDOWPOS_CENTERED, int windowWidth = 800, int windowHeight = 600, int flags = SDL_WINDOW_SHOWN) override;
	void Loop() override;
	void Start() override;

	void SetBackground(const std::string& BGpath) override;
	int CountOfBricks() const override;
	bool IsEnd() override;

	
private:
	std::unique_ptr<SDL_Window, void(*)(SDL_Window*)> window { nullptr, SDL_DestroyWindow };
	std::unique_ptr<Background> background;

	std::vector<std::unique_ptr<Wall>> walls;
	std::vector<std::unique_ptr<Ball>> balls;
	std::vector<std::unique_ptr<Player>> players;
	std::vector<std::unique_ptr<Brick>> bricks;
	std::vector<std::unique_ptr<Bubble>> bubbles;
	std::vector<std::unique_ptr<Bomb>> bombs;


	const float deltaTime = 1000.0f / FPS;
	std::chrono::time_point<std::chrono::high_resolution_clock> firstFrame, secondFrame, firstUpdate, secondUpdate;
	std::chrono::milliseconds durationFrame, durationUpdate;

	SDL_Rect gameOverRect;
	bool isEnd;

	void AddWall(SDL_Rect dstBox, const std::string& path, int characterWidth) override;
	void AddPlayer(SDL_Rect dstBox, const std::string& path, int characterWidth) override;
	void AddBall(SDL_Rect dstBox, const std::string& path, int characterWidth) override;
	void AddBrick(SDL_Rect dstBox, const std::string& path, int characterWidth) override;
	void AddBubble(SDL_Rect dstBox, const std::string& path, int characterWidth) override;
	void AddBomb(SDL_Rect dstBox, const std::string& path, int characterWidth) override;

	void Basket();
	void Render();
	void Update();
	void HandleEvents();
	void Collision();
};