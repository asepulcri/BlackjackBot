#include <iostream>
#include "../include/card.h"
#include "../include/shoe.h"
#include "../include/player.h"

int main() {

	shoes::shoe gameShoe(1);

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

		player1.clearHand();
		dealer1.clearHand();

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
			switch (player1Decision) {
				case players::Decisions::doubledown:
					if (player1.getHandSize() == int(2)) {
						std::cout << "Player doubled down" << std::endl;
						player1.drawCard(gameShoe.drawCard());
						std::cout << "Player drew: " << std::endl;
						player1.showLastDrawnCard();
						player1.betHand(playerBet);
						playerBet *= 2;
					}
					else
						player1Decision = players::Decisions::hit;
					break;

				case players::Decisions::hit:
					std::cout << "Player hit" << std::endl;
					player1.drawCard(gameShoe.drawCard());
					std::cout << "Player drew: " << std::endl;
					player1.showLastDrawnCard();
					break;
			}

			player1Decision = player1.makeDecision(dealer1.getFaceUpCard());
		}

		if (player1.getHandValue() > int(21)) {
			std::cout << "You've busted" << std::endl;
			continue;
		}

		dealer1.revealHand();

		std::cout << "Dealer's hand is: " << std::endl;

		dealer1.showHand();

		while (dealer1Decision != players::Decisions::stand) {
			if (dealer1Decision == players::Decisions::hit) {
				std::cout << "Dealer hit" << std::endl;
				dealer1.drawCard(gameShoe.drawCard());
				std::cout << "Dealer drew: " << std::endl;
				dealer1.showLastDrawnCard();
			}

			dealer1Decision = dealer1.makeDecision();

		}

		if (dealer1.getHandValue() > int(21)) {
			std::cout << "Dealer busted" << std::endl;
			player1.winMoney(playerBet * 2);
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

	std::cout << "You ran out of money" << std::endl;

	return 0;
}
