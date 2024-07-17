#pragma once
class RendererComponent {
public:
	SDL_Rect dstBox;
	SDL_Rect srcBox;
	SDL_Rect windowRect;

	std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)> texture { nullptr, Texture::Delete };

	virtual void Render();
private:

};

