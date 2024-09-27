#include "Game.h"

int main() {
	Game newGame;
	
	for(int i = 0; i < 10; i++){
		newGame.playShoe();
		newGame.resetShoe();
	}

	return 0;
}