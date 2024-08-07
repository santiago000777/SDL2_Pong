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
	static const SRenderer& Get();
	SDL_Rect& WindowRect() const;
	SDL_Renderer* Renderer() const;

private:
	static SDL_Renderer* renderer;
	static SDL_Rect windowRect;
	SDL_Window* window;
};
