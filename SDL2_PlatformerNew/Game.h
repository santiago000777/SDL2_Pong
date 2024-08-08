#pragma once
#include "Player.h"
#include "Ball.h"
#include "Background.h"
#include "Wall.h"
#include "Renderer.h"
#include "Brick.h"
#include "Bubble.h"
#include "Bomb.h"

#define FPS		60

class Game {
public:
	Game(){}
	Game(const Game& rhs) = delete;
	Game(Game&& rhs) = delete;
	~Game();

	void operator=(const Game& rhs) = delete;
	void operator=(Game&& rhs) = delete;

	static void Init(const std::string& windowName = "Window", int posX = SDL_WINDOWPOS_CENTERED,
					 int posY = SDL_WINDOWPOS_CENTERED, int windowWidth = 800, int windowHeight = 600, int flags = SDL_WINDOW_SHOWN);
	static void Loop();
	static void Start();

	template <typename Ty> 
	static void AddObject(SDL_Rect dstBox, const std::string& path, int characterWidth);
	template<> static void AddObject<Wall>(SDL_Rect dstBox, const std::string& path, int characterWidth) {
		walls.push_back(std::make_unique<Wall>(dstBox, path, characterWidth));
	}
	template<> static void AddObject<Player>(SDL_Rect dstBox, const std::string& path, int characterWidth) {
		players.push_back(std::make_unique<Player>(dstBox, path, characterWidth));
	}
	template<> static void AddObject<Ball>(SDL_Rect dstBox, const std::string& path, int characterWidth) {
		balls.push_back(std::make_unique<Ball>(dstBox, path, characterWidth));
	}
	template<> static void AddObject<Brick>(SDL_Rect dstBox, const std::string& path, int characterWidth) {
		bricks.push_back(std::make_unique<Brick>(dstBox, path, characterWidth));
	}
	template<> static void AddObject<Bubble>(SDL_Rect dstBox, const std::string& path, int characterWidth) {
		bubbles.push_back(std::make_unique<Bubble>(dstBox, path, characterWidth));
	}
	template<> static void AddObject<Bomb>(SDL_Rect dstBox, const std::string& path, int characterWidth) {
		bombs.push_back(std::make_unique<Bomb>(dstBox, path, characterWidth));
	}

	static const Game& Get();
	static void SetBackground(const std::string& BGpath);

	int CountOfBricks() const;

	static bool IsEnd();
private:
	static std::unique_ptr<SDL_Window, void(*)(SDL_Window*)> window;
	static std::unique_ptr<Background> background;

	static std::vector<std::unique_ptr<Wall>> walls;
	static std::vector<std::unique_ptr<Ball>> balls;
	static std::vector<std::unique_ptr<Player>> players;
	static std::vector<std::unique_ptr<Brick>> bricks;
	static std::vector<std::unique_ptr<Bubble>> bubbles;
	static std::vector<std::unique_ptr<Bomb>> bombs;


	static const float deltaTime;
	static std::chrono::time_point<std::chrono::high_resolution_clock> firstFrame, secondFrame, firstUpdate, secondUpdate;
	static std::chrono::milliseconds durationFrame, durationUpdate;

	static SDL_Rect gameOverRect;

	static bool isEnd;

	static void Basket();
	static void Render();
	static void Update();
	static void HandleEvents();
	static void Collision();
};
