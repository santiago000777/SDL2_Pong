#pragma once
class MoveComponent {
public:
	TVec2 vector;
	bool collision[4];
	bool isDestroyble = false;

	bool IsDestroyble();
	virtual void HandleEvents();
	virtual void Update(std::vector<Object*>* otherObjects, float delta);
	enum eIndex : int {
		LEFT = 0,
		RIGHT,
		UP,
		DOWN
	};
	SDL_Rect GetDstBox() const;
private:
	void CollisionPoint(std::vector<Object*>* otherObjects, float delta);
};

