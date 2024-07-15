#include "common.h"
#include "Player.h"

Player::Player(SDL_Renderer* renderer, SDL_Rect dstBox, const std::string& path, SDL_Rect from, SDL_Rect windowRect)
	: Object(renderer, dstBox, path, from, windowRect) {

	vector.x = 1;
	vector.y = 1;
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
//	rhs.background = NULL;
//
//	this->renderer = rhs.renderer;
//	rhs.renderer = NULL;
//
//	this->texture = rhs.texture;
//	rhs.texture = NULL;
//}

void Player::HandleEvents() {
	if (this->collision[eIndex::UP]) {
		vector.y *= -1;
	}
	if (this->collision[eIndex::DOWN]) {
		vector.y *= -1;
	}
	if (this->collision[eIndex::LEFT]) {
		vector.x *= -1;
	}
	if (this->collision[eIndex::RIGHT]) {
		vector.x *= -1;
	}
}
