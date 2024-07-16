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
	if (PressedKey(eControls::UP)) {
		vector.y = -1;
	}
	if (PressedKey(eControls::LEFT)) {
		vector.x = -1;
	}
	if (PressedKey(eControls::DOWN)) {
		vector.y = 1;
	}
	if (PressedKey(eControls::RIGHT)) {
		vector.x = 1;
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
