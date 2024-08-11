#include "Bubble.h"

Bubble::Bubble(Vec4f box, const std::string& path, int characterWidth)
	: MovableObject(box, path, characterWidth) {

	isDestroyble = false;
	std::random_device randomNum;
	std::uniform_real_distribution<float> dist(0.05f, 0.2f);

	std::uniform_int_distribution<int> decide(0, 3);


	if (decide(randomNum) == 0) {
		vector = { dist(randomNum), dist(randomNum) };
	} else if (decide(randomNum) == 1) {
		vector = { -dist(randomNum), -dist(randomNum) };
	} else if (decide(randomNum) == 2) {
		vector = { -dist(randomNum), dist(randomNum) };
	} else {
		vector = { dist(randomNum), -dist(randomNum) };
	}

	std::cout << vector.x << "  " << vector.y << "\n";

	std::uniform_int_distribution<int> position(200, 500);

	this->box.x = (float)position(randomNum);
	this->box.y = (float)position(randomNum);
}

Bubble::~Bubble() {
	std::cout << "Deleted Bubble\n";
}

void Bubble::Update() {

	if (!this->collision[LEFT] && !this->collision[RIGHT] && !this->collision[UP] && !this->collision[DOWN]) {
		this->box.x += vector.x * MovableObject::deltaT;
		this->box.y += vector.y * MovableObject::deltaT;
		currentSprite = 0;
		return;
	}
	if (this->isDestroyble) {
		isAlive = false;
		return;
	}

	if (this->collision[eIndex::UP]) {
		currentSprite = UP + 1;
		vector.y *= -1;
	}
	if (this->collision[eIndex::DOWN]) {
		currentSprite = DOWN + 1;
		vector.y *= -1;
	}
	if (this->collision[eIndex::LEFT]) {
		currentSprite = LEFT + 1;
		vector.x *= -1;
	}
	if (this->collision[eIndex::RIGHT]) {
		currentSprite = RIGHT + 1;
		vector.x *= -1;
	}

	if (this->collision[LEFT]) {

		if (this->vector.x > 0 && !this->collision[RIGHT])
			this->box.x += this->vector.x * MovableObject::deltaT;

		if (this->vector.y < 0 && !this->collision[UP]
			|| this->vector.y > 0 && !this->collision[DOWN]) {

			this->box.y += this->vector.y * MovableObject::deltaT;
		}
	}
	if (this->collision[RIGHT]) {

		if (this->vector.x < 0 && !this->collision[LEFT]) {
			this->box.x += this->vector.x * MovableObject::deltaT;
		}
		if (this->vector.y < 0 && !this->collision[UP]
			|| this->vector.y > 0 && !this->collision[DOWN]) {

			this->box.y += this->vector.y * MovableObject::deltaT;
		}
	}
	if (this->collision[UP]) {

		if (this->vector.y > 0 && !this->collision[DOWN])
			this->box.y += this->vector.y * MovableObject::deltaT;

		if (this->vector.x < 0 && !this->collision[LEFT]
			|| this->vector.x > 0 && !this->collision[RIGHT]) {

			this->box.x += this->vector.x * MovableObject::deltaT;
		}
	}
	if (this->collision[DOWN]) {

		if (this->vector.y < 0 && !this->collision[UP])
			this->box.y += this->vector.y * MovableObject::deltaT;

		if (this->vector.x < 0 && !this->collision[LEFT]
			|| this->vector.x > 0 && !this->collision[RIGHT]) {

			this->box.x += this->vector.x * MovableObject::deltaT;
		}
	}

	this->collision[LEFT] = false;
	this->collision[RIGHT] = false;
	this->collision[UP] = false;
	this->collision[DOWN] = false;
}