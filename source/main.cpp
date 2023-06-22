#include <iostream>
#include "../include/card.h"
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

	cards::card dealerUpcard = dealer1.getFaceUpCard();

	players::Decisions player1Decision = player1.makeDecision(dealer1.getFaceUpCard());

	std::cout << "Player Card Total = " << playerHandValue << std::endl;
	std::cout << "Dealer Upcard = " << std::to_underlying(dealerUpcard.getRank()) << std::endl;
	std::cout << "Decision = " << player1Decision << std::endl;

	return 0;
}
