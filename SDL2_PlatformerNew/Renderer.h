#pragma once

class SRenderer {
public:
	SRenderer() {}
	SRenderer(const SRenderer& rhs)	= delete;
	SRenderer(SRenderer&& rhs) = delete;
	~SRenderer();

	void operator=(const SRenderer& rhs) = delete;
	void operator=(SRenderer&& rhs) = delete;

	static void Init(SDL_Window* window, SDL_Rect rect);
	static SRenderer& Get();
	const SDL_Rect& WindowRect();
	SDL_Renderer* Renderer();

private:
	static SDL_Renderer* renderer;
	static SDL_Rect windowRect;
	SDL_Window* window;
};
