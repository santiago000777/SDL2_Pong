#include "common.h"
#include "Renderer.h"

SDL_Renderer* SRenderer::renderer = nullptr;
SRenderer sRenderer;


SRenderer::~SRenderer() {
	SDL_DestroyRenderer(renderer);
	std::cout << "Deleted Renderer\n";
}

void SRenderer::Init(SDL_Window* window) {
	if (renderer == nullptr) {
		renderer = SDL_CreateRenderer(window, -1, 1);
	}
}

SRenderer& SRenderer::Get(/*SDL_Window* window*/) {
	return sRenderer;
}

SDL_Renderer* SRenderer::Renderer() {
	return renderer;
}

//SRenderer& Get() {
//	return sRenderer;
//}
