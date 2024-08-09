#pragma once
#include "common.h"

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

	//template <typename Ty>
	virtual void AddObject(SDL_Rect dstBox, const std::string& path, int characterWidth) = 0;

protected:
	IGame() {}
	~IGame() {}
};

namespace Game {
	extern IGame& Get();
};