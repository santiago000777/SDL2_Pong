#include "MovableObject.h"

float MovableObject::deltaT = 0.0f;


bool MovableObject::Collision(MovableObject& object, const Object& other) {

	SDL_Rect box1 = { object.dstBox.x + (int)roundf(object.vector.x * MovableObject::deltaT), object.dstBox.y + (int)roundf(object.vector.y * MovableObject::deltaT), object.dstBox.w, object.dstBox.h };
	SDL_Rect box2 = { other.GetDstBox().x, other.GetDstBox().y, other.GetDstBox().w, other.GetDstBox().h };

	auto LeftEdge = [](const SDL_Rect& box) -> int { return box.x; };
	auto RightEdge = [](const SDL_Rect& box) -> int { return box.x + box.w; };
	auto UpEdge = [](const SDL_Rect& box) -> int { return box.y; };
	auto DownEdge = [](const SDL_Rect& box) -> int { return box.y + box.h; };

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
	SDL_Rect box1 = { object.dstBox.x + (int)roundf(object.vector.x * MovableObject::deltaT), object.dstBox.y + (int)roundf(object.vector.y * MovableObject::deltaT), object.dstBox.w, object.dstBox.h };

	auto LeftEdge = [](const SDL_Rect& box) -> int { return box.x; };
	auto RightEdge = [](const SDL_Rect& box) -> int { return box.x + box.w; };
	auto UpEdge = [](const SDL_Rect& box) -> int { return box.y; };
	auto DownEdge = [](const SDL_Rect& box) -> int { return box.y + box.h; };

	if (RightEdge(box1) > LeftEdge(other) && LeftEdge(box1) < RightEdge(other)
		&& DownEdge(box1) > UpEdge(other) && UpEdge(box1) < DownEdge(other)) {

		if (abs(UpEdge(box1) - DownEdge(other)) < abs(DownEdge(box1) - UpEdge(other))) {

			if (abs(UpEdge(box1) - DownEdge(other)) < abs(LeftEdge(box1) - RightEdge(other))
				&& abs(UpEdge(box1) - DownEdge(other)) < abs(RightEdge(box1) - LeftEdge(other))) {
				std::cout << "Up\n";
				object.collision[UP] = true;
			} else {
				if (abs(LeftEdge(box1) - RightEdge(other)) < abs(RightEdge(box1) - LeftEdge(other))) {
					std::cout << "Left\n";
					object.collision[LEFT] = true;
				} else {
					std::cout << "Right\n";
					object.collision[RIGHT] = true;
				}
			}
		} else {
			if (abs(DownEdge(box1) - UpEdge(other)) < abs(LeftEdge(box1) - RightEdge(other))
				&& abs(DownEdge(box1) - UpEdge(other)) < abs(RightEdge(box1) - LeftEdge(other))) {

				std::cout << "Down\n";
				object.collision[DOWN] = true;
			} else {
				if (abs(LeftEdge(box1) - RightEdge(other)) < abs(RightEdge(box1) - LeftEdge(other))) {
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

	if (RightEdge(object.GetDstBox()) > LeftEdge(other) && LeftEdge(object.GetDstBox()) < RightEdge(other)
		&& DownEdge(object.GetDstBox()) > UpEdge(other) && UpEdge(object.GetDstBox()) < DownEdge(other)) {

		if (abs(UpEdge(object.GetDstBox()) - DownEdge(other)) < abs(DownEdge(object.GetDstBox()) - UpEdge(other))) {

			if (abs(UpEdge(object.GetDstBox()) - DownEdge(other)) < abs(LeftEdge(object.GetDstBox()) - RightEdge(other))
				&& abs(UpEdge(object.GetDstBox()) - DownEdge(other)) < abs(RightEdge(object.GetDstBox()) - LeftEdge(other))) {
				std::cout << "Up\n";
			} else {
				if (abs(LeftEdge(object.GetDstBox()) - RightEdge(other)) < abs(RightEdge(object.GetDstBox()) - LeftEdge(other))) {
					std::cout << "Left\n";
				} else {
					std::cout << "Right\n";
				}
			}
		} else {
			if (abs(DownEdge(object.GetDstBox()) - UpEdge(other)) < abs(LeftEdge(object.GetDstBox()) - RightEdge(other))
				&& abs(DownEdge(object.GetDstBox()) - UpEdge(other)) < abs(RightEdge(object.GetDstBox()) - LeftEdge(other))) {

				std::cout << "Down\n";
			} else {
				if (abs(LeftEdge(object.GetDstBox()) - RightEdge(other)) < abs(RightEdge(object.GetDstBox()) - LeftEdge(other))) {
					std::cout << "Left\n";
				} else {
					std::cout << "Right\n";
				}
			}
		}
		return true;
	} else {
		return false;
	}
}

const std::string& MovableObject::GetPath() const {
	return path;
}

const Vec2 MovableObject::GetVector() const {
	return vector;
}

bool MovableObject::Collision(MovableObject& object, MovableObject& other) {
	SDL_Rect box1 = { object.dstBox.x + (int)roundf(object.vector.x * MovableObject::deltaT), object.dstBox.y + (int)roundf(object.vector.y * MovableObject::deltaT), object.dstBox.w, object.dstBox.h };
	SDL_Rect box2 = { other.dstBox.x + (int)roundf(other.vector.x * MovableObject::deltaT), other.dstBox.y + (int)roundf(other.vector.y * MovableObject::deltaT), other.dstBox.w, other.dstBox.h };

	auto LeftEdge = [](const SDL_Rect& box) -> int { return box.x; };
	auto RightEdge = [](const SDL_Rect& box) -> int { return box.x + box.w; };
	auto UpEdge = [](const SDL_Rect& box) -> int { return box.y; };
	auto DownEdge = [](const SDL_Rect& box) -> int { return box.y + box.h; };

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
				} else {
					std::cout << "Right\n";
					object.collision[RIGHT] = true;
					other.collision[LEFT] = true;
				}
			}
		} else {
			if (abs(DownEdge(box1) - UpEdge(box2)) < abs(LeftEdge(box1) - RightEdge(box2))
				&& abs(DownEdge(box1) - UpEdge(box2)) < abs(RightEdge(box1) - LeftEdge(box2))) {

				std::cout << "Down\n";
				object.collision[DOWN] = true;
				other.collision[UP] = true;
			} else {
				if (abs(LeftEdge(box1) - RightEdge(box2)) < abs(RightEdge(box1) - LeftEdge(box2))) {
					std::cout << "Left\n";
					object.collision[LEFT] = true;
					other.collision[RIGHT] = true;
				} else {
					std::cout << "Right\n";
					object.collision[RIGHT] = true;
					other.collision[LEFT] = true;
				}
			}
		}
		return true;
	} else {
		return false;
	}
}

MovableObject::MovableObject(SDL_Rect dstBox, const std::string& path, int characterWidth)
	: Object(dstBox, path, characterWidth), path(path) {

}

MovableObject::~MovableObject() {

}