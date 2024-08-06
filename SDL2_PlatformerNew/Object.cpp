#include "Object.h"

SDL_Rect Object::GetDstBox() const {
	return dstBox;
}

int Object::GetSpriteWidth() const {
	return srcBox.w;
}

int Object::GetCurrentSprite() const {
	return currentSprite;
}

void Object::ChangeSprite() {
	currentSprite++;
}

// Jestli jakykoli roh Rect se nachazi v kruhu ->
		// vzdalenost prepony rohu od stredu kruhu je <= radius
bool Object::Collision(const Object& object, const Circle& circle) {

	auto TopLeftCorner = [](const Object& object) -> Vec2 { return { (float)object.GetDstBox().x, (float)object.GetDstBox().y }; };
	auto TopRightCorner = [](const Object& object) -> Vec2 { return { (float)object.GetDstBox().x + (float)object.GetDstBox().w, (float)object.GetDstBox().y }; };
	auto BottomLeftCorner = [](const Object& object) -> Vec2 { return { (float)object.GetDstBox().x, (float)object.GetDstBox().y + (float)object.GetDstBox().h }; };
	auto BottomRightCorner = [](const Object& object) -> Vec2 { return { (float)object.GetDstBox().x + (float)object.GetDstBox().w, (float)object.GetDstBox().y + (float)object.GetDstBox().h }; };

	auto LeftEdge = [](const Object& object) -> int { return object.GetDstBox().x; };
	auto RightEdge = [](const Object& object) -> int { return object.GetDstBox().x + object.GetDstBox().w; };
	auto UpEdge = [](const Object& object) -> int { return object.GetDstBox().y; };
	auto DownEdge = [](const Object& object) -> int { return object.GetDstBox().y + object.GetDstBox().h; };

	auto Hypotenuse = [](float a, float b) -> float {
		return sqrtf(powf(fabsf(a), 2.0f) + powf(fabsf(b), 2.0f));
	};

	if (circle.center.x + circle.radius < LeftEdge(object) || circle.center.x - circle.radius > RightEdge(object)
	|| circle.center.y + circle.radius < UpEdge(object) || circle.center.y - circle.radius > DownEdge(object)) {

		return false;
	}
	if (circle.center.x - circle.radius >= LeftEdge(object) || circle.center.x + circle.radius <= RightEdge(object)
	|| circle.center.y - circle.radius >= UpEdge(object) || circle.center.y + circle.radius <= DownEdge(object)) {

		return true;
	}
	if (Hypotenuse(TopLeftCorner(object).x - circle.center.x, TopLeftCorner(object).y - circle.center.y) <= circle.radius
	|| Hypotenuse(TopRightCorner(object).x - circle.center.x, TopRightCorner(object).y - circle.center.y) <= circle.radius
	|| Hypotenuse(BottomLeftCorner(object).x - circle.center.x, BottomLeftCorner(object).y - circle.center.y) <= circle.radius
	|| Hypotenuse(BottomRightCorner(object).x - circle.center.x, BottomRightCorner(object).y - circle.center.y) <= circle.radius) {

		return true;
	}
}

//bool Object::IsDestroyble() const {
//	return isDestroyble;
//}

void Object::Render() {
	srcBox.x = srcBox.w * currentSprite;
	SDL_RenderCopy(SRenderer::Get().Renderer(), texture.get(), &srcBox, &dstBox);
}

Object::Object(SDL_Rect dstBox, const std::string& path, int characterWidth)
	: dstBox(dstBox) {

	Picture picture = Picture::Create(path, 255, 0, 255, 255);
	srcBox = picture.GetSrcBox();
	sprites = srcBox.w / characterWidth;
	srcBox.w = characterWidth;

	texture.reset(picture.GetTexture());
}
