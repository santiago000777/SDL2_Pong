#include "common.h"
#include "Renderer.h"

SRenderer sRenderer;
IRenderer& Renderer::Get() {
	return sRenderer;
}

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

const SDL_Rect& SRenderer::WindowRect() const {
	return windowRect;
}

SDL_Renderer* SRenderer::Renderer() const {
	return renderer;
}

