#pragma once
#include "common.h"
#include "Player.h"
#include "Ball.h"
#include "Wall.h"
#include "Brick.h"
#include "Bubble.h"
#include "Bomb.h"

class IGame {
public:
	IGame(const IGame& rhs) = default;
	IGame(IGame&& rhs) = default;

	void operator=(const IGame& rhs) = delete;
	void operator=(IGame&& rhs) = delete;

	virtual void Init(const std::string& windowName = "Window", int posX = SDL_WINDOWPOS_CENTERED,
					  int posY = SDL_WINDOWPOS_CENTERED, int windowWidth = 800, int windowHeight = 600, int flags = SDL_WINDOW_SHOWN) = 0;
	virtual void Loop() = 0;
	virtual void Start() = 0;
	virtual void SetBackground(const std::string& BGpath) = 0;
	virtual int CountOfBricks() const = 0;
	virtual bool IsEnd() = 0;


	template <typename Ty>
	void Add(SDL_Rect dstBox, const std::string& path, int characterWidth);
	template<> void Add<Wall>(SDL_Rect dstBox, const std::string& path, int characterWidth) override {
		AddWall(dstBox, path, characterWidth);
	}
	template<> void Add<Player>(SDL_Rect dstBox, const std::string& path, int characterWidth) override {
		AddPlayer(dstBox, path, characterWidth);
	}
	template<> void Add<Ball>(SDL_Rect dstBox, const std::string& path, int characterWidth) override {
		AddBall(dstBox, path, characterWidth);
	}
	template<> void Add<Brick>(SDL_Rect dstBox, const std::string& path, int characterWidth) override {
		AddBrick(dstBox, path, characterWidth);
	}
	template<> void Add<Bubble>(SDL_Rect dstBox, const std::string& path, int characterWidth) override {
		AddBubble(dstBox, path, characterWidth);
	}
	template<> void Add<Bomb>(SDL_Rect dstBox, const std::string& path, int characterWidth) override {
		AddBomb(dstBox, path, characterWidth);
	}

	virtual void AddWall(SDL_Rect dstBox, const std::string& path, int characterWidth) = 0;
	virtual void AddPlayer(SDL_Rect dstBox, const std::string& path, int characterWidth) = 0;
	virtual void AddBall(SDL_Rect dstBox, const std::string& path, int characterWidth) = 0;
	virtual void AddBrick(SDL_Rect dstBox, const std::string& path, int characterWidth) = 0;
	virtual void AddBubble(SDL_Rect dstBox, const std::string& path, int characterWidth) = 0;
	virtual void AddBomb(SDL_Rect dstBox, const std::string& path, int characterWidth) = 0;
protected:
	IGame() {}
	~IGame() {}

};

namespace Game {
	extern IGame& Get();
};