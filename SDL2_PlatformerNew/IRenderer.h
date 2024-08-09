#pragma once
#include "common.h"

class IRenderer {
public:
	IRenderer(const IRenderer& rhs) = delete;
	IRenderer(IRenderer&& rhs) = delete;

	void operator=(const IRenderer& rhs) = delete;
	void operator=(IRenderer&& rhs) = delete;

	virtual void Init(SDL_Window* window, SDL_Rect rect) = 0;
	virtual const SDL_Rect& WindowRect() const = 0;
	virtual SDL_Renderer* Renderer() const = 0;

protected:
	~IRenderer(){}
	//virtual ~IRenderer() = 0;
	IRenderer(){}
};

namespace Renderer {
	extern IRenderer& Get();
};