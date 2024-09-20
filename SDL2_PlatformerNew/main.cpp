#include "common.h"
#include "IGame.h"
// ERROR -> musim vnitrne pocitat pozici bez zaokrouhleni -> zaokrouhlit az pri vykresleni
// TODO: Pridat Text
//		 Pridat kruhovou kolizi na Bomb
//       Pridat Menu

int main(int argc, char* args[]) {
	Game::Get().Init("PONG", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 604, 850, SDL_WINDOW_SHOWN);
	Game::Get().Start();

	while (!Game::Get().IsEnd()) {
		Game::Get().Loop();
	}

	if (Game::Get().CountOfBricks() > 0) {
		std::cout << "Game over!\n\n";
	}
	else {
		std::cout << "You won!\n\n";
	}

	return 0;
}


// Git commands
/*
	--CREATE GITHUB REPO--
	* git init									-> vytvoreni .git
	* git branch -M <branch>					-> tvorba nove branch
	* git remote add origin <pathFromGitHub>	-> vytvoreni remote s cestou, ktera se generuje na GitHubu -> musi se rucne repo vytvorit
	* git remote -v								-> kontrola remotu
		...

	--CLONE GITHUB REPO--
	* git clone <pathFromGitHub>				-> kopirovani repo z github

	--PULL--
	* git log									-> zobrazeni vsech commitu
	* git pull origin <branch>					-> nahrani do visual studia

	--COMMIT & PUSH--
	* git status								-> rozdily mezi kodem a poslednim commitem

	* git add <path>							-> pridani daneho souboru, ktery se zmenil, ke commitu
	* git add .									-> pridani vsech souboru, ktery se zmenil, ke commitu
	* git rm -r --cached <path>					-> odebrani zmeny

	* git commit -m "<msg>"						-> commit se zpravou
	* git push origin <branch>					-> nahrani do githubu

	--CHECKOUT--
	* git checkout <branch>						-> prechazeni na novou branch
	* git checkout <commit>						-> vraceni na dany commit
*/