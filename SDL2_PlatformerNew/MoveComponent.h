#pragma once
#include "common.h"

class MoveComponent {
public:

	MoveComponent(SDL_Rect dstBox);
		
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

protected:
	SDL_Rect dstBox;
	TVec2 vector;
	bool isDestroyble = false;
	bool collision[4];

private:
	void CollisionPoint(std::vector<MoveComponent*>* others, float delta);
};

