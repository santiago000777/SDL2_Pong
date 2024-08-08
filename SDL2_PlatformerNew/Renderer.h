#pragma once
#include "IRenderer.h"

class SRenderer : public IRenderer {
public:
	SRenderer() {}
	SRenderer(const SRenderer& rhs) = delete;
	SRenderer(SRenderer&& rhs) = delete;
	~SRenderer()/* override*/;

	void operator=(const SRenderer& rhs) = delete;
	void operator=(SRenderer&& rhs) = delete;

	void Init(SDL_Window* window, SDL_Rect rect) override;
	const SDL_Rect& WindowRect() const override;
	SDL_Renderer* Renderer() const override;

private:
	SDL_Renderer* renderer = nullptr;
	SDL_Rect windowRect { 0, 0, 0, 0 };
	SDL_Window* window;
};