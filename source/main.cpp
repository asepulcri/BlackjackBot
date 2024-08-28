#include <iostream>
#include <memory>
#include "Card.h"
#include "Shoe.h"
#include "Player.h"

int main() {

	Shoe gameShoe(5);

	gameShoe.shuffleShoe();

	Player player1;
	Dealer dealer1;

	player1.drawCard(std::make_unique<Card> (Suit(spades), Rank(ace)));
	player1.drawCard(std::make_unique<Card> (Suit(clubs), Rank(ace)));

	dealer1.drawCard(gameShoe.drawCard());
	dealer1.drawCard(gameShoe.drawCard());
	
	dealer1.checkUpCard();

	Decisions player1Decision = player1.makeDecision(dealer1.getUpCard());

	Decisions dealer1Decision = dealer1.makeDecision();

	return 0;
}
