#include "MoveComponent.h"

bool MoveComponent::IsDestroyble() {
	return isDestroyble;
}

void MoveComponent::Update(std::vector<MoveComponent*>* others, float delta) {
	CollisionPoint(others, delta);

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
	if (!this->collision[LEFT] && !this->collision[RIGHT] && !this->collision[UP] && !this->collision[DOWN]) {
		this->dstBox.x += roundf(vector.x * delta);
		this->dstBox.y += roundf(vector.y * delta);
	}
}

SDL_Rect MoveComponent::GetDstBox() const {
	return dstBox;
}

void MoveComponent::CollisionPoint(std::vector<MoveComponent*>* others, float delta) {
	this->collision[LEFT] = false;
	this->collision[RIGHT] = false;
	this->collision[UP] = false;
	this->collision[DOWN] = false;

	for (auto object : *others) {
		if (object == this) {
			continue;
		}

		if ((this->dstBox.x + this->vector.x * delta + this->dstBox.w > object->GetDstBox().x && this->dstBox.x + this->vector.x * delta < object->GetDstBox().x + object->GetDstBox().w)
			&& (this->dstBox.y + this->vector.y * delta + this->dstBox.h > object->GetDstBox().y && this->dstBox.y + this->vector.y * delta < object->GetDstBox().y + object->GetDstBox().h)) {

			if (this->vector.x * delta > 0 && this->dstBox.x + this->dstBox.w >= object->GetDstBox().x
				&& this->dstBox.y < object->GetDstBox().y + object->GetDstBox().h && this->dstBox.y + this->dstBox.h > object->GetDstBox().y) {

				this->collision[RIGHT] = true;
				std::cout << "RIGHT\n";
			}
			if (this->vector.x * delta < 0 && this->dstBox.x <= object->GetDstBox().x + object->GetDstBox().w
				&& this->dstBox.y < object->GetDstBox().y + object->GetDstBox().h && this->dstBox.y + this->dstBox.h > object->GetDstBox().y) {

				this->collision[LEFT] = true;
				std::cout << "LEFT\n";
			}
			if (this->vector.y * delta > 0 && this->dstBox.y + this->dstBox.h >= object->GetDstBox().y
				&& this->dstBox.x < object->GetDstBox().x + object->GetDstBox().w && this->dstBox.x + this->dstBox.w > object->GetDstBox().x) {

				this->collision[DOWN] = true;
				std::cout << "DOWN\n";
			}
			if (this->vector.y * delta < 0 && this->dstBox.y <= object->GetDstBox().y + object->GetDstBox().h
				&& this->dstBox.x < object->GetDstBox().x + object->GetDstBox().w && this->dstBox.x + this->dstBox.w > object->GetDstBox().x) {

				this->collision[UP] = true;
				std::cout << "UP\n";
			}
		}
	}
}
