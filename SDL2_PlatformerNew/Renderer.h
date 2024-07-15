#pragma once
//#include "SDL.h"

class SRenderer {
public:
	SRenderer() {}/* = delete;*/
	SRenderer(const SRenderer& rhs) = delete;
	SRenderer(SRenderer&& rhs) = delete;
	~SRenderer();

	void operator=(const SRenderer& rhs) = delete;
	void operator=(SRenderer&& rhs) = delete;

	static void Init(SDL_Window* window);
	static SRenderer& Get();
	SDL_Renderer* Renderer();

private:
	static SDL_Renderer* renderer;
	SDL_Window* window;
};

//extern SRenderer& Get();