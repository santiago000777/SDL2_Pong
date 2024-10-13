#include "Object.h"

Object::Object(Vec4f box, const std::string& path, int characterWidth)
	: box(box), path(path) {


	SDL_Texture* picture;
	std::tie(picture, srcBox) = CreateTexture(path, 255, 0, 255, 255);

	sprites = srcBox.w / characterWidth;
	srcBox.w = characterWidth;

	texture.reset(picture);
}

Object::Object(Object&& rhs) {
	box = rhs.box;
	srcBox = rhs.srcBox;
	isDestroyble = rhs.isDestroyble;
	currentSprite = rhs.currentSprite;
	isAlive = rhs.isAlive;
}

const std::string& Object::GetPath() const {
	return path;
}

Vec4f Object::GetBox() const {
	return box;
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

	auto TopLeftCorner = [](const Object& object) -> Vec2 { return { object.GetBox().x, object.GetBox().y }; };
	auto TopRightCorner = [](const Object& object) -> Vec2 { return { object.GetBox().x + object.GetBox().w, object.GetBox().y }; };
	auto BottomLeftCorner = [](const Object& object) -> Vec2 { return { object.GetBox().x, object.GetBox().y + object.GetBox().h }; };
	auto BottomRightCorner = [](const Object& object) -> Vec2 { return { object.GetBox().x + object.GetBox().w, object.GetBox().y + object.GetBox().h }; };

	auto LeftEdge = [](const Object& object) -> float { return object.GetBox().x; };
	auto RightEdge = [](const Object& object) -> float { return object.GetBox().x + object.GetBox().w; };
	auto UpEdge = [](const Object& object) -> float { return object.GetBox().y; };
	auto DownEdge = [](const Object& object) -> float { return object.GetBox().y + object.GetBox().h; };

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

void Object::Render() {
	srcBox.x = srcBox.w * currentSprite;
	SDL_Rect roundedBox = box.Get();
	SDL_RenderCopy(Renderer::Get().Renderer(), texture.get(), &srcBox, &roundedBox);
}

