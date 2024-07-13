#include "common.h"
#include "Player.h"

Player::Player(SDL_Renderer* renderer, SDL_Rect dstBox, const std::string& path, SDL_Rect from, SDL_Rect windowRect)
	: Object(renderer, dstBox, path, from, windowRect) {

	vector.x = 1;
	vector.y = 1;
}

Player::Player(Player&& rhs)
	: Object(std::move(rhs)) {
}

Player::~Player() {
	std::cout << "Deleted player\n";
}

void Player::operator=(const Player& rhs) {
}

void Player::operator=(Player&& rhs) {
}

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
