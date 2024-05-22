#include "game.h"
#include "card.h"
#include "stdlib.h"
#include <clocale>

int main() {
	system("Chcp 1251");
	setlocale(LC_ALL, "RU");
	int amount_players = 4;
	Game game = Game(amount_players);
	Card* card = new Card();
	game.GameStart();
	
}