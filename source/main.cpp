#include "Game.h"

int main() {
	Game newGame;

	// Play 10 shoes
	for(int i = 0; i < 10; i++){
		newGame.playShoe();
		newGame.resetShoe();
	}

	// Write player stats to TXT file
	newGame.writeStatstoTXT();

	return 0;
}