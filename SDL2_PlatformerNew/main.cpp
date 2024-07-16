#include "common.h"
#include "Game.h"

	// pridat rozdilne kontejney (players, walls, ...)
		// -> pridani k players isAlive

int main(int argc, char* args[]) {
	Game game("TITLE", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 600, SDL_WINDOW_SHOWN); // SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED

	for (int i = 0; i < 6; i++) {
		game.AddObject<Object>({ 300, 90 * i, 30, 90 }, "Pictures/verticalWall.bmp", { 0, 0, 7, 9 });
	}
	for (int i = 0; i < 6; i++) {
		game.AddObject<Object>({ 900, 90 * i, 30, 90 }, "Pictures/verticalWall.bmp", { 0, 0, 7, 9 });
	}
	for (int i = 0; i < 10; i++) {
		game.AddObject<Object>({ 330 + (70 * i), 0, 90, 30 }, "Pictures/horizontalWall.bmp", { 0, 0, 9, 7 });
	}
	/*for (int i = 0; i < 10; i++) {
		game.AddObject<Object>({ 330 + (70 * i), 540, 90, 30 }, "Pictures/horizontalWall.bmp", { 0, 0, 9, 7 });
	}*/
	game.AddObject<Player>({ 550, 500, 100, 24 }, "Pictures/paddle.bmp", { 0, 0, 25, 6 });

	const float ballScale = 3.0f;
	game.AddObject<Ball>({ 400, 100, (int)roundf(7 * ballScale), (int)roundf(7 * ballScale) }, "Pictures/BallBmp.bmp", { 0, 0, 7, 8 });

	game.SetBackground("Pictures/veitImg.bmp");

	while (!PressedKey(VK_SPACE)) {
		game.Loop();
	}

	// opravit vraceni u drzeni left i right nebo up i down klavesy

	return 0;
}