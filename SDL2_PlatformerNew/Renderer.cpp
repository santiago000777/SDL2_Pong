#include "common.h"
#include "Renderer.h"

SDL_Renderer* SRenderer::renderer = nullptr;
SDL_Rect SRenderer::windowRect { 0, 0, 0, 0 };
SRenderer sRenderer;

SRenderer::~SRenderer() {
	SDL_DestroyRenderer(renderer);
	renderer = nullptr;

	std::cout << "Deleted Renderer\n";
}

void SRenderer::Init(SDL_Window* window, SDL_Rect rect) {
	if (renderer == nullptr) {
		windowRect = rect;
		renderer = SDL_CreateRenderer(window, -1, 1);
	}
}

const SRenderer& SRenderer::Get() {
	return sRenderer;
}

SDL_Rect& SRenderer::WindowRect() const {
	return windowRect;
}

SDL_Renderer* SRenderer::Renderer() const {
	return renderer;
}
