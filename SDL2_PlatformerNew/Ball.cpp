#include "Ball.h"

Ball::Ball(SDL_Rect dstBox, const std::string& path, int characterWidth)
	: MovableObject(dstBox, path, characterWidth) {

	std::random_device randomNum;
	std::uniform_real_distribution<float> dist(0.1f, 0.4f);

	std::uniform_int_distribution<int> decide(0, 3);

	
	if (decide(randomNum) == 0) {
		vector = { dist(randomNum), dist(randomNum) };
	}
	else if(decide(randomNum) == 1) {
		vector = { -dist(randomNum), -dist(randomNum) };
	}
	else if (decide(randomNum) == 2) {
		vector = { -dist(randomNum), dist(randomNum) };
	}
	else {
		vector = { dist(randomNum), -dist(randomNum) };
	}
	
	std::cout << vector.x << "  " << vector.y << "\n";
}


Ball::~Ball() {
	std::cout << "Deleted ball\n";
}

//void Ball::operator=(const Ball& rhs) {
//	this->dstBox = rhs.dstBox;
//	this->srcBox = rhs.srcBox;
//	this->windowRect = rhs.windowRect;
//	this->isDestroyble = rhs.isDestroyble;
//	
//	this->vector = rhs.vector;
//
//	this->renderer = rhs.renderer;
//	this->texture = Texture::Create(renderer, path);
//	*this->background = *rhs.background;
//	memcpy(this->collision, rhs.collision, 4 * sizeof(bool));
//}

//void Ball::operator=(Ball&& rhs) {
//	this->dstBox = rhs.dstBox;
//	this->srcBox = rhs.srcBox;
//	this->windowRect = rhs.windowRect;
//	this->isDestroyble = rhs.isDestroyble;
//	this->path = rhs.path;
//	this->vector = rhs.vector;
//	
//	memcpy(this->collision, rhs.collision, 4 * sizeof(bool));
//	
//	this->background = rhs.background;
//	rhs.background = nullptr;
//	
//	this->renderer = rhs.renderer;
//	rhs.renderer = nullptr;
//	
//	this->texture = rhs.texture;
//	rhs.texture = nullptr;
//}

void Ball::SetOwnerId(int id) {
	playerOwnerId = id;
}

int Ball::GetOwnerId() const {
	return playerOwnerId;
}

int Ball::GetPoints() const {
	return points;
}

void Ball::AddPoints(int points) {
	this->points += points;
}


void Ball::Update() {

	if (!this->collision[LEFT] && !this->collision[RIGHT] && !this->collision[UP] && !this->collision[DOWN]) {
		this->dstBox.x += roundf(vector.x * MovableObject::deltaT);
		this->dstBox.y += roundf(vector.y * MovableObject::deltaT);
		currentSprite = 0;
		return;
	}
	if (this->isDestroyble) {
		isAlive = false;
		return;
	}

	if (this->collision[eIndex::UP]) {
		currentSprite = UP + 1;
		if (vector.y < 0)
			vector.y *= -1;
	}
	if (this->collision[eIndex::DOWN]) {
		currentSprite = DOWN + 1;
		if (vector.y > 0)
			vector.y *= -1;
	}
	if (this->collision[eIndex::LEFT]) {
		currentSprite = LEFT + 1;
		if(vector.x < 0)
			vector.x *= -1;
	}
	if (this->collision[eIndex::RIGHT]) {
		currentSprite = RIGHT + 1;
		if (vector.x > 0)
			vector.x *= -1;
	}


	if (this->collision[LEFT]) {

		if (this->vector.x > 0 && !this->collision[RIGHT])
			this->dstBox.x += roundf(this->vector.x * MovableObject::deltaT);

		if (this->vector.y < 0 && !this->collision[UP]
			|| this->vector.y > 0 && !this->collision[DOWN]) {

			this->dstBox.y += roundf(this->vector.y * MovableObject::deltaT);
		}
	}
	if (this->collision[RIGHT]) {

		if (this->vector.x < 0 && !this->collision[LEFT]) {
			this->dstBox.x += roundf(this->vector.x * MovableObject::deltaT);
		}
		if (this->vector.y < 0 && !this->collision[UP]
			|| this->vector.y > 0 && !this->collision[DOWN]) {

			this->dstBox.y += roundf(this->vector.y * MovableObject::deltaT);
		}
	}
	if (this->collision[UP]) {

		if (this->vector.y > 0 && !this->collision[DOWN])
			this->dstBox.y += roundf(this->vector.y * MovableObject::deltaT);

		if (this->vector.x < 0 && !this->collision[LEFT]
			|| this->vector.x > 0 && !this->collision[RIGHT]) {

			this->dstBox.x += roundf(this->vector.x * MovableObject::deltaT);
		}
	}
	if (this->collision[DOWN]) {

		if (this->vector.y < 0 && !this->collision[UP])
			this->dstBox.y += roundf(this->vector.y * MovableObject::deltaT);

		if (this->vector.x < 0 && !this->collision[LEFT]
			|| this->vector.x > 0 && !this->collision[RIGHT]) {

			this->dstBox.x += roundf(this->vector.x * MovableObject::deltaT);
		}
	}

	this->collision[LEFT] = false;
	this->collision[RIGHT] = false;
	this->collision[UP] = false;
	this->collision[DOWN] = false;
}

void Ball::ResetPoints() {
	points = 0;
}

void Ball::ResetPosition() {
	dstBox.x = 300;
	dstBox.y = 200;

	std::random_device randomNum;
	std::uniform_real_distribution<float> dist(0.1f, 0.4f);

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
}
