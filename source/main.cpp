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

		std::cout << "Your hand is: " << std::endl;
		player1.showHand();

		std::cout << "Dealer faceup card is: ";
		dealer1.showFaceUpCard();

		players::Decisions player1Decision = player1.makeDecision(dealer1.getFaceUpCard());
		players::Decisions dealer1Decision = dealer1.makeDecision();

		while (player1Decision != players::Decisions::stand) {
			if (player1Decision == players::Decisions::hit)
				player1.drawCard(gameShoe.drawCard());

			if (player1Decision == players::Decisions::doubledown) {
				player1.drawCard(gameShoe.drawCard());
				player1.betHand(playerBet);
				playerBet *= 2;
			}

			player1Decision = player1.makeDecision(dealer1.getFaceUpCard());
		}

		if (player1.getHandValue() > int(21)) {
			std::cout << "You've busted" << std::endl;
			continue;
		}

		while (dealer1Decision != players::Decisions::stand) {
			if (dealer1Decision == players::Decisions::hit)
				dealer1.drawCard(gameShoe.drawCard());

			dealer1Decision = dealer1.makeDecision();

		}
		if (dealer1.getHandValue() > int(21)) {
			std::cout << "Dealer busted" << std::endl;
			player1.winMoney(playerBet);
			continue;
		}

		if (player1.getHandValue() > dealer1.getHandValue()) {
			std::cout << "You won the hand" << std::endl;
			player1.winMoney(playerBet * 2);
			continue;
		}
		else {
			std::cout << "Dealer won the hand" << std::endl;
			continue;
		}
	}

	return 0;
}
