#include <iostream>
#include "../include/shoe.h"
#include "../include/player.h"

int main() {

	shoes::shoe gameShoe(5);

	gameShoe.shuffleShoe();

	players::player player1;

	players::dealer dealer1;

	for (int i = 0; i < 2; i++) {
		player1.drawCard(gameShoe.drawCard());

		dealer1.drawCard(gameShoe.drawCard());
	}

	int playerHandValue = player1.getHandValue();

	dealer1.revealHand();

	int dealerHandValue = dealer1.getHandValue();

	players::Decisions dealerDecision = dealer1.makeDecision();

	while (dealerDecision == players::Decisions::hit)
		dealer1.drawCard(gameShoe.drawCard());

	return 0;
}
