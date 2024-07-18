#include "RendererComponent.h"

RendererComponent::RendererComponent(SDL_Rect from, SDL_Rect windowRect)
	: srcBox(from), windowRect(windowRect) {
}

//void RendererComponent::Render() {
//	SDL_RenderCopy(SRenderer::Get().Renderer(), texture.get(), &srcBox, &dstBox);
//}
