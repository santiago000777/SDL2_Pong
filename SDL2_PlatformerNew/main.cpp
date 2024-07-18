#include "common.h"
#include "Game.h"

	// pridat rozdilne kontejney (players, walls, ...)
		// -> pridani k players isAlive

int main(int argc, char* args[]) {
	Game game("TITLE", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 604, 850, SDL_WINDOW_SHOWN); // SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED
	game.SetBackground("Pictures/veitImg.bmp");
	game.AddObject<Wall>({ 25, 80, 30, 90 * 8 }, "Pictures/verticalWall.bmp", { 0, 0, 7, 9 });
	game.AddObject<Wall>({ 25 + 525, 80, 30, 90 * 8 }, "Pictures/verticalWall.bmp", { 0, 0, 7, 9 });

	game.AddObject<Wall>({ 25, 50, 550, 30 }, "Pictures/horizontalWall.bmp", { 0, 0, 9, 7 });
	
	//game.AddObject<Wall>({ 25, 750, 550, 30 }, "Pictures/horizontalWall.bmp", { 0, 0, 9, 7 });

	game.AddObject<Player>({ 300, 750, 100, 24 }, "Pictures/paddle.bmp", { 0, 0, 25, 6 });

	const float ballScale = 3.0f;
	game.AddObject<Ball>({ 300, 100, (int)roundf(7 * ballScale), (int)roundf(7 * ballScale) }, "Pictures/BallBmp.bmp", { 0, 0, 7, 8 });

	while (!PressedKey(VK_SPACE) && !game.IsGameOver()) {
		game.Loop();
	}

	// opravit vraceni u drzeni left i right nebo up i down klavesy

	std::cout << "Game over!\n\n";
	return 0;
}