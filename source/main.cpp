#include <iostream>
#include <memory>
#include "Card.h"
#include "Shoe.h"
#include "Player.h"

int main() {

	Shoe gameShoe(5);

	gameShoe.shuffleShoe();

	Player player1;

	player1.drawCard(gameShoe.drawCard());

	return 0;
}
