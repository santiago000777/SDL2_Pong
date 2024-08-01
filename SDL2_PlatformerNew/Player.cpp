#include "common.h"
#include "Player.h"

int Player::playerCount = 0;

Player::Player(SDL_Rect dstBox, const std::string& path, int characterWidth, SDL_Rect windowRect)
	: MovableObject(dstBox, path, characterWidth, windowRect) {
	idPlayer = playerCount;
	playerCount++;
}

//Player::Player(const Player& rhs) 
//	: Object(rhs) {
//}
//
//Player::Player(Player&& rhs)
//	: Object(std::move(rhs)) {
//}

Player::~Player() {
	std::cout << "Deleted player\n";
}

//void Player::operator=(const Player& rhs) {
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
//
//void Player::operator=(Player&& rhs) {
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

void Player::HandleEvents() {
	vector.x = 0;
	vector.y = 0;

	if (PressedKey((short)eControls::LEFT)) {
		vector.x += -1;
	}
	if (PressedKey((short)eControls::RIGHT)) {
		vector.x += 1;
	}
}

void Player::Update() {
	if (points > 0) {
		std::cout << "Player - " << points << "\n";
	}
	if (!this->collision[LEFT] && !this->collision[RIGHT] && !this->collision[UP] && !this->collision[DOWN]) {
		this->dstBox.x += roundf(vector.x * MovableObject::deltaT);
		this->dstBox.y += roundf(vector.y * MovableObject::deltaT);
	}
	else {
		if (this->isDestroyble) {
			isAlive = false;
			return;
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
}

int Player::GetPlayerId() const {
	return idPlayer;
}

void Player::AddPoints(int points) {
	this->points += points;
}

bool Player::IsGameOver() {
	if(lives <= 0)
		return true;
	return false;
}

void Player::DecreaseLives(int i) {
	lives -= i;
}

void Player::ResetPosition() {
	dstBox.x = 255;
	dstBox.y = 750;
}
