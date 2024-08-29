#include <iostream>
#include <memory>
#include "Card.h"
#include "Shoe.h"
#include "Player.h"

int main() {

	Shoe gameShoe(5);

	gameShoe.shuffleShoe();

	Player player1;

	player1.drawCard(0, std::make_unique<Card> (Suit(spades), Rank(ace)));
	player1.drawCard(0, std::make_unique<Card> (Suit(clubs), Rank(ace)));

	return 0;
}
