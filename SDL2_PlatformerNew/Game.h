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
	Game(const std::string& windowName = "Window", int posX = SDL_WINDOWPOS_CENTERED,
		 int posY = SDL_WINDOWPOS_CENTERED, int windowWidth = 800, int windowHeight = 600, int flags = SDL_WINDOW_SHOWN);
	Game(const Game& rhs) = delete;
	Game(Game&& rhs) = delete;
	~Game();

	void operator=(const Game& rhs) = delete;
	void operator=(Game&& rhs) = delete;

	void Loop();
	void Start();

	template <typename Ty> void AddObject(SDL_Rect dstBox, const std::string& path, int characterWidth);
	template<> void AddObject<Wall>(SDL_Rect dstBox, const std::string& path, int characterWidth) {
		//auto wall = new Wall(dstBox, path, characterWidth);
		
		//walls.push_back(wall);
		walls.push_back(std::make_unique<Wall>(dstBox, path, characterWidth));
	}
	template<> void AddObject<Player>(SDL_Rect dstBox, const std::string& path, int characterWidth) {
		//auto player = new Player(dstBox, path, characterWidth);
		
		//players.push_back(player);
		players.push_back(std::make_unique<Player>(dstBox, path, characterWidth));
	}
	template<> void AddObject<Ball>(SDL_Rect dstBox, const std::string& path, int characterWidth) {
		//auto ball = new Ball(dstBox, path, characterWidth);
		
		//balls.push_back(ball);
		balls.push_back(std::make_unique<Ball>(dstBox, path, characterWidth));
	}
	template<> void AddObject<Brick>(SDL_Rect dstBox, const std::string& path, int characterWidth) {
		//auto brick = new Brick(dstBox, path, characterWidth);

		//bricks.push_back(brick);
		bricks.push_back(std::make_unique<Brick>(dstBox, path, characterWidth));
	}
	template<> void AddObject<Bubble>(SDL_Rect dstBox, const std::string& path, int characterWidth) {
		//auto bubble = new Bubble(dstBox, path, characterWidth);

		//bubbles.push_back(bubble);
		bubbles.push_back(std::make_unique<Bubble>(dstBox, path, characterWidth));
	}
	template<> void AddObject<Bomb>(SDL_Rect dstBox, const std::string& path, int characterWidth) {
		bombs.push_back(std::make_unique<Bomb>(dstBox, path, characterWidth));
	}

	void SetBackground(const std::string& BGpath);

	int GetCountOfBricks() const;

	bool IsEnd();
private:
		//std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)> texture { nullptr, Picture::DeleteTexture };
	std::unique_ptr<SDL_Window, void(*)(SDL_Window*)> window { nullptr, SDL_DestroyWindow };
	//SDL_Window* window;
	std::unique_ptr<Background> background;
	//Background* background;

	std::vector<std::unique_ptr<Wall>> walls;//
	std::vector<std::unique_ptr<Ball>> balls;
	std::vector<std::unique_ptr<Player>> players;
	std::vector<std::unique_ptr<Brick>> bricks;
	std::vector<std::unique_ptr<Bubble>> bubbles;

	std::vector<std::unique_ptr<Bomb>> bombs;

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
