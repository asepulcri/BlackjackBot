#include <iostream>
#include "../include/card.h"
#include "../include/shoe.h"
#include "../include/player.h"

int main() {

	shoes::shoe gameShoe(5);

	gameShoe.shuffleShoe();

	int playerBuyIn;

	std::cout << "Enter how many chips you want to buy in: ";

	std::cin >> playerBuyIn;

	players::player player1(playerBuyIn);

	players::dealer dealer1;

	while (player1.getWalletValue() > int(0)) {
		int playerBet;
		
		std::cout << "Enter how many chips you want to bet: ";

		std::cin >> playerBet;

		player1.betHand(playerBet);

		for (int i = 0; i < 2; i++) {
			player1.drawCard(gameShoe.drawCard());
			dealer1.drawCard(gameShoe.drawCard());
		}

		while (player1.getHandValue() < int(21) || dealer1.getHandValue() < int(21)) {
		}
	}

	return 0;
}
