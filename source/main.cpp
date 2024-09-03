#include <iostream>
#include <memory>
#include "Card.h"
#include "HighLowStrategy.h"
#include "Player.h"
#include "Shoe.h"

int main() {

	Shoe gameShoe(6);

	gameShoe.shuffleShoe();

	Player player1;
	Dealer dealer1;
	std::unique_ptr<HighLowStrategy> hiLo = std::make_unique<HighLowStrategy>();

	if(gameShoe.getDecksRemaining() > 1.5){
		// Start gameplay loop
		
		// Dealer draws card
		dealer1.drawCard(gameShoe.drawCard(), hiLo);
		
		// Player game loop
		for(int i = 0; i < player1.getLastHandIdx() + 1; i ++) {
			
			// Player draws cards and decides what to do
			player1.drawCard(i, gameShoe.drawCard(), hiLo);
			player1.drawCard(i, gameShoe.drawCard(), hiLo);
			Decisions player1Decision = player1.makeDecision(i, dealer1.getUpCardRank());
			
			// Place bets
			player1.betHand(hiLo, 10);
			
			// Player plays turn
			while(player1Decision != stand) {
				if(player1Decision = hit)
					player1.drawCard(i, gameShoe.drawCard(), hiLo);

				if(player1Decision = split)
					player1.drawCard(i, gameShoe.drawCard(), hiLo);
					player1.betHand(hiLo, 10);
			}

			if(player1.getHandValue(i) > 21){
				std::cout << "Player busted" << std::endl;
				player1.updateWallet(0);
			}

		}

		// Dealer plays turn
		dealer1.drawCard(gameShoe.drawCard(), hiLo);
		Decisions dealer1Decision = dealer1.makeDecision();
		while(dealer1Decision != stand) {
			if(dealer1Decision = hit)
				dealer1.drawCard(gameShoe.drawCard(), hiLo);
		}

		if(dealer1.getHandValue() > 21) {
			std::cout << "Dealer busted" << std::endl;
			player1.updateWallet(1);
		}
		
	}

	return 0;
}