#pragma once
#include "common.h"

class MoveComponent {
public:
	TVec2 vector;

	bool IsDestroyble();
	virtual void HandleEvents() = 0;
	virtual void Update(std::vector<MoveComponent*>* others, float delta);
	enum eIndex : int {
		LEFT = 0,
		RIGHT,
		UP,
		DOWN
	};
	SDL_Rect GetDstBox() const;

private:
	bool collision[4];
	bool isDestroyble = false;
	SDL_Rect dstBox;
	void CollisionPoint(std::vector<MoveComponent*>* others, float delta);
};

