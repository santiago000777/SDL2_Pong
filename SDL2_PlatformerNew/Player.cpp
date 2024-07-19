#include "common.h"
#include "Player.h"

Player::Player(SDL_Rect dstBox, const std::string& path, SDL_Rect from, SDL_Rect windowRect) 
	: Object(dstBox, path, from, windowRect) {
	
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
	if (PressedKey((short)eControls::UP)) {
		vector.y = -1;
	}
	if (PressedKey((short)eControls::LEFT)) {
		vector.x = -1;
	}
	if (PressedKey((short)eControls::DOWN)) {
		vector.y = 1;
	}
	if (PressedKey((short)eControls::RIGHT)) {
		vector.x = 1;
	}
}

void Player::Update(float delta) {
	

	if (!this->collision[LEFT] && !this->collision[RIGHT] && !this->collision[UP] && !this->collision[DOWN]) {
		this->dstBox.x += roundf(vector.x * delta);
		this->dstBox.y += roundf(vector.y * delta);
	}
	else {
		if (this->isDestroyble) {
			delete this;
			return;
		}

		if (this->collision[LEFT]) {

			if (this->vector.x > 0 && !this->collision[RIGHT])
				this->dstBox.x += roundf(this->vector.x * delta);

			if (this->vector.y < 0 && !this->collision[UP]
				|| this->vector.y > 0 && !this->collision[DOWN]) {

				this->dstBox.y += roundf(this->vector.y * delta);
			}
		}
		if (this->collision[RIGHT]) {
			

			if (this->vector.x < 0 && !this->collision[LEFT]) {
				this->dstBox.x += roundf(this->vector.x * delta);
			}
			if (this->vector.y < 0 && !this->collision[UP]
				|| this->vector.y > 0 && !this->collision[DOWN]) {

				this->dstBox.y += roundf(this->vector.y * delta);
			}
		}
		if (this->collision[UP]) {

			if (this->vector.y > 0 && !this->collision[DOWN])
				this->dstBox.y += roundf(this->vector.y * delta);

			if (this->vector.x < 0 && !this->collision[LEFT]
				|| this->vector.x > 0 && !this->collision[RIGHT]) {

				this->dstBox.x += roundf(this->vector.x * delta);
			}
		}
		if (this->collision[DOWN]) {

			if (this->vector.y < 0 && !this->collision[UP])
				this->dstBox.y += roundf(this->vector.y * delta);

			if (this->vector.x < 0 && !this->collision[LEFT]
				|| this->vector.x > 0 && !this->collision[RIGHT]) {

				this->dstBox.x += roundf(this->vector.x * delta);
			}
		}
	}
	
	this->collision[LEFT] = false;
	this->collision[RIGHT] = false;
	this->collision[UP] = false;
	this->collision[DOWN] = false;
}

void Player::Collision(Wall* object, float delta) {
	if ((this->dstBox.x + this->vector.x * delta + this->dstBox.w > object->GetDstBox().x && this->dstBox.x + this->vector.x * delta < object->GetDstBox().x + object->GetDstBox().w)
		&& (this->dstBox.y + this->vector.y * delta + this->dstBox.h > object->GetDstBox().y && this->dstBox.y + this->vector.y * delta < object->GetDstBox().y + object->GetDstBox().h)) {

		if (this->vector.x * delta > 0 && this->dstBox.x + this->dstBox.w >= object->GetDstBox().x
			&& this->dstBox.y < object->GetDstBox().y + object->GetDstBox().h && this->dstBox.y + this->dstBox.h > object->GetDstBox().y) {

			this->collision[RIGHT] = true;
			std::cout << "Player - RIGHT\n";
		}
		if (this->vector.x * delta < 0 && this->dstBox.x <= object->GetDstBox().x + object->GetDstBox().w
			&& this->dstBox.y < object->GetDstBox().y + object->GetDstBox().h && this->dstBox.y + this->dstBox.h > object->GetDstBox().y) {

			this->collision[LEFT] = true;
			std::cout << "Player - LEFT\n";
		}
		if (this->vector.y * delta > 0 && this->dstBox.y + this->dstBox.h >= object->GetDstBox().y
			&& this->dstBox.x < object->GetDstBox().x + object->GetDstBox().w && this->dstBox.x + this->dstBox.w > object->GetDstBox().x) {

			this->collision[DOWN] = true;
			std::cout << "Player - DOWN\n";
		}
		if (this->vector.y * delta < 0 && this->dstBox.y <= object->GetDstBox().y + object->GetDstBox().h
			&& this->dstBox.x < object->GetDstBox().x + object->GetDstBox().w && this->dstBox.x + this->dstBox.w > object->GetDstBox().x) {

			this->collision[UP] = true;
			std::cout << "Player - UP\n";
		}

		if (object->IsDestroyble()) {
			delete object;
			return;
		}
	}
}

bool Player::IsGameOver() {
	if(lives <= 0)
		return true;
	return false;
}

void Player::DecreaseLives(int i) {
	lives -= i;
}
