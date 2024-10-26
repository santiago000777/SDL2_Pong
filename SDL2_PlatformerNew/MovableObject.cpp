#include "MovableObject.h"

float MovableObject::deltaT = 0.0f;


bool MovableObject::Collision(MovableObject& object, const Object& other) {

	Vec4f box1 = { object.box.x + object.vector.x * MovableObject::deltaT, object.box.y + object.vector.y * MovableObject::deltaT, object.box.w, object.box.h };
	Vec4f box2 = { other.GetBox().x, other.GetBox().y, other.GetBox().w, other.GetBox().h };

	auto LeftEdge = [](const Vec4f& box) -> float { return box.x; };
	auto RightEdge = [](const Vec4f& box) -> float { return box.x + box.w; };
	auto UpEdge = [](const Vec4f& box) -> float { return box.y; };
	auto DownEdge = [](const Vec4f& box) -> float { return box.y + box.h; };

	if (RightEdge(box1) > LeftEdge(box2) && LeftEdge(box1) < RightEdge(box2)
		&& DownEdge(box1) > UpEdge(box2) && UpEdge(box1) < DownEdge(box2)) {

		if (abs(UpEdge(box1) - DownEdge(box2)) < abs(DownEdge(box1) - UpEdge(box2))) {

			if (abs(UpEdge(box1) - DownEdge(box2)) < abs(LeftEdge(box1) - RightEdge(box2))
				&& abs(UpEdge(box1) - DownEdge(box2)) < abs(RightEdge(box1) - LeftEdge(box2))) {
				std::cout << "Up\n";
				object.collision[UP] = true;
			} else {
				if (abs(LeftEdge(box1) - RightEdge(box2)) < abs(RightEdge(box1) - LeftEdge(box2))) {
					std::cout << "Left\n";
					object.collision[LEFT] = true;
				} else {
					std::cout << "Right\n";
					object.collision[RIGHT] = true;
				}
			}
		} else {
			if (abs(DownEdge(box1) - UpEdge(box2)) < abs(LeftEdge(box1) - RightEdge(box2))
				&& abs(DownEdge(box1) - UpEdge(box2)) < abs(RightEdge(box1) - LeftEdge(box2))) {

				std::cout << "Down\n";
				object.collision[DOWN] = true;
			} else {
				if (abs(LeftEdge(box1) - RightEdge(box2)) < abs(RightEdge(box1) - LeftEdge(box2))) {
					std::cout << "Left\n";
					object.collision[LEFT] = true;
				} else {
					std::cout << "Right\n";
					object.collision[RIGHT] = true;
				}
			}
		}
		return true;
	} else {
		return false;
	}
}

bool MovableObject::Collision(MovableObject& object, const SDL_Rect& other) {
	Vec4f box1 = { object.box.x + object.vector.x * MovableObject::deltaT, object.box.y + object.vector.y * MovableObject::deltaT, object.box.w, object.box.h };
	Vec4f box2 = { (float)other.x, (float)other.y, (float)other.w, (float)other.h };

	auto LeftEdge = [](const Vec4f& box) -> float { return box.x; };
	auto RightEdge = [](const Vec4f& box) -> float { return box.x + box.w; };
	auto UpEdge = [](const Vec4f& box) -> float { return box.y; };
	auto DownEdge = [](const Vec4f& box) -> float { return box.y + box.h; };

	if (RightEdge(box1) > LeftEdge(box2) && LeftEdge(box1) < RightEdge(box2)
		&& DownEdge(box1) > UpEdge(box2) && UpEdge(box1) < DownEdge(box2)) {

		if (abs(UpEdge(box1) - DownEdge(box2)) < abs(DownEdge(box1) - UpEdge(box2))) {

			if (abs(UpEdge(box1) - DownEdge(box2)) < abs(LeftEdge(box1) - RightEdge(box2))
				&& abs(UpEdge(box1) - DownEdge(box2)) < abs(RightEdge(box1) - LeftEdge(box2))) {
				std::cout << "Up\n";
				object.collision[UP] = true;
			} else {
				if (abs(LeftEdge(box1) - RightEdge(box2)) < abs(RightEdge(box1) - LeftEdge(box2))) {
					std::cout << "Left\n";
					object.collision[LEFT] = true;
				} else {
					std::cout << "Right\n";
					object.collision[RIGHT] = true;
				}
			}
		} else {
			if (abs(DownEdge(box1) - UpEdge(box2)) < abs(LeftEdge(box1) - RightEdge(box2))
				&& abs(DownEdge(box1) - UpEdge(box2)) < abs(RightEdge(box1) - LeftEdge(box2))) {

				std::cout << "Down\n";
				object.collision[DOWN] = true;
			} else {
				if (abs(LeftEdge(box1) - RightEdge(box2)) < abs(RightEdge(box1) - LeftEdge(box2))) {
					std::cout << "Left\n";
					object.collision[LEFT] = true;
				} else {
					std::cout << "Right\n";
					object.collision[RIGHT] = true;
				}
			}
		}
		return true;
	} else {
		return false;
	}
}

bool MovableObject::Collision(const Object& object, const SDL_Rect& other) {

	auto LeftEdge = [](const SDL_Rect& box) -> int { return box.x; };
	auto RightEdge = [](const SDL_Rect& box) -> int { return box.x + box.w; };
	auto UpEdge = [](const SDL_Rect& box) -> int { return box.y; };
	auto DownEdge = [](const SDL_Rect& box) -> int { return box.y + box.h; };

	if (RightEdge(object.GetBox().Get()) > LeftEdge(other) && LeftEdge(object.GetBox().Get()) < RightEdge(other)
		&& DownEdge(object.GetBox().Get()) > UpEdge(other) && UpEdge(object.GetBox().Get()) < DownEdge(other)) {

		if (abs(UpEdge(object.GetBox().Get()) - DownEdge(other)) < abs(DownEdge(object.GetBox().Get()) - UpEdge(other))) {

			if (abs(UpEdge(object.GetBox().Get()) - DownEdge(other)) < abs(LeftEdge(object.GetBox().Get()) - RightEdge(other))
				&& abs(UpEdge(object.GetBox().Get()) - DownEdge(other)) < abs(RightEdge(object.GetBox().Get()) - LeftEdge(other))) {
				std::cout << "Up\n";
			} else {
				if (abs(LeftEdge(object.GetBox().Get()) - RightEdge(other)) < abs(RightEdge(object.GetBox().Get()) - LeftEdge(other))) {
					std::cout << "Left\n";
				} else {
					std::cout << "Right\n";
				}
			}
		} 
		else {
			if (abs(DownEdge(object.GetBox().Get()) - UpEdge(other)) < abs(LeftEdge(object.GetBox().Get()) - RightEdge(other))
				&& abs(DownEdge(object.GetBox().Get()) - UpEdge(other)) < abs(RightEdge(object.GetBox().Get()) - LeftEdge(other))) {

				std::cout << "Down\n";
			} else {
				if (abs(LeftEdge(object.GetBox().Get()) - RightEdge(other)) < abs(RightEdge(object.GetBox().Get()) - LeftEdge(other))) {
					std::cout << "Left\n";
				} else {
					std::cout << "Right\n";
				}
			}
		}
		return true;
	} 
	else {
		return false;
	}
}

const Vec2 MovableObject::GetVector() const {
	return vector;
}

bool MovableObject::Collision(MovableObject& object, MovableObject& other) {
	Vec4f box1 = { object.box.x + object.vector.x * MovableObject::deltaT, object.box.y + object.vector.y * MovableObject::deltaT, object.box.w, object.box.h };
	Vec4f box2 = { other.box.x + other.vector.x * MovableObject::deltaT, other.box.y + other.vector.y * MovableObject::deltaT, other.box.w, other.box.h };

	auto LeftEdge = [](const Vec4f& box) -> int { return box.x; };
	auto RightEdge = [](const Vec4f& box) -> int { return box.x + box.w; };
	auto UpEdge = [](const Vec4f& box) -> int { return box.y; };
	auto DownEdge = [](const Vec4f& box) -> int { return box.y + box.h; };

	if (RightEdge(box1) > LeftEdge(box2) && LeftEdge(box1) < RightEdge(box2)
		&& DownEdge(box1) > UpEdge(box2) && UpEdge(box1) < DownEdge(box2)) {

		if (abs(UpEdge(box1) - DownEdge(box2)) < abs(DownEdge(box1) - UpEdge(box2))) {

			if (abs(UpEdge(box1) - DownEdge(box2)) < abs(LeftEdge(box1) - RightEdge(box2))
				&& abs(UpEdge(box1) - DownEdge(box2)) < abs(RightEdge(box1) - LeftEdge(box2))) {
				std::cout << "Up\n";
				object.collision[UP] = true;
				other.collision[DOWN] = true;
			} else {
				if (abs(LeftEdge(box1) - RightEdge(box2)) < abs(RightEdge(box1) - LeftEdge(box2))) {
					std::cout << "Left\n";
					object.collision[LEFT] = true;
					other.collision[RIGHT] = true;
				} 
				else {
					std::cout << "Right\n";
					object.collision[RIGHT] = true;
					other.collision[LEFT] = true;
				}
			}
		} 
		else {
			if (abs(DownEdge(box1) - UpEdge(box2)) < abs(LeftEdge(box1) - RightEdge(box2))
				&& abs(DownEdge(box1) - UpEdge(box2)) < abs(RightEdge(box1) - LeftEdge(box2))) {

				std::cout << "Down\n";
				object.collision[DOWN] = true;
				other.collision[UP] = true;
			} 
			else {
				if (abs(LeftEdge(box1) - RightEdge(box2)) < abs(RightEdge(box1) - LeftEdge(box2))) {
					std::cout << "Left\n";
					object.collision[LEFT] = true;
					other.collision[RIGHT] = true;
				} 
				else {
					std::cout << "Right\n";
					object.collision[RIGHT] = true;
					other.collision[LEFT] = true;
				}
			}
		}
		return true;
	} 
	else {
		return false;
	}
}

MovableObject::MovableObject(Vec4f box, const std::string& path, int characterWidth)
	: Object(box, path, characterWidth) {

}

MovableObject::MovableObject(MovableObject&& rhs) 
	: Object(std::move(rhs)) {

	vector = rhs.vector;
	
	memcpy(collision, rhs.collision, 4 * sizeof(bool));
	
}

MovableObject::~MovableObject() {

}