#include "common.h"
#include "Game.h"

	// chybna kolize u balonu + player + wall v rohu
	// pridat deltaTime
	// pridat animace

int main(int argc, char* args[]) {
	Game game("PONG", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 604, 850, SDL_WINDOW_SHOWN); // SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED
	game.SetBackground("Pictures/veitImg.bmp");
	game.AddObject<Wall>({ 25, 80, 30, 90 * 8 }, "Pictures/verticalWall.bmp", { 0, 0, 7, 9 });
	game.AddObject<Wall>({ 25 + 525, 80, 30, 90 * 8 }, "Pictures/verticalWall.bmp", { 0, 0, 7, 9 });

	game.AddObject<Wall>({ 25, 50, 550, 30 }, "Pictures/horizontalWall.bmp", { 0, 0, 9, 7 });
	
	game.AddObject<Wall>({ 25, 780, 550, 30 }, "Pictures/horizontalWall.bmp", { 0, 0, 9, 7 });

	game.AddObject<Player>({ 56, 750, 100, 24 }, "Pictures/paddle.bmp", { 0, 0, 25, 6 });

	const float ballScale = 3.0f;
	game.AddObject<Ball>({ 300, 200, (int)roundf(7 * ballScale), (int)roundf(7 * ballScale) }, "Pictures/BallBmp.bmp", { 0, 0, 7, 8 });

	for (int i = 0; i < 6; i++) {
		game.AddObject<Brick>({ 120 + 64 * i, 100, 64, 20 }, "Pictures/Brick.bmp", { 0, 0, 16, 5 });
	}

	while (!PressedKey(VK_SPACE) && !game.IsGameOver()) {
		game.Loop();
	}
	
	// opravit vraceni u drzeni left i right nebo up i down klavesy

		std::cout << "Game over!\n\n";

	return 0;
}

	// Git commands
/*

	--PULL--
	* git log					-> zobrazeni vsech commitu
	* git pull origin <branch>	-> nahrani do visual studia
	
	--COMMIT&PUSH--
	* git status				-> rozdily mezi kodem a poslednim commitem

	* git add <path>			-> pridani daneho souboru, ktery se zmenil, ke commitu
	* git add -A				-> pridani vsech souboru, ktery se zmenil, ke commitu
	
	* git commit -m "<msg>"		-> commit se zpravou
	* git push origin <branch>	-> nahrani do githubu 
	
	--CHECKOUT--
	* git checkout <branch>		-> prechazeni na novou branch
	* git checkout <commit>		-> vraceni na dany commit

*/