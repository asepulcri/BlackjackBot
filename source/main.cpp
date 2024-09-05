#include <iostream>
#include <memory>
#include "Card.h"
#include "Player.h"
#include "Shoe.h"

int main() {

	Shoe gameShoe(6);

	gameShoe.shuffleShoe();

	Player player1;
	Dealer dealer1;


	if(gameShoe.getDecksRemaining() > 1.5){
		// Start gameplay loop
		
		// Dealer draws card
		dealer1.drawCard(gameShoe.drawCard());
		
		// Player game loop
		for(int i = 0; i < player1.getLastHandIdx() + 1; i ++) {
			
			// Player draws cards and decides what to do
			player1.drawCard(i, gameShoe.drawCard());
			player1.drawCard(i, gameShoe.drawCard());
			Decisions player1Decision = player1.makeDecision(i, dealer1.getUpCardRank());
			
			// Place bets
			player1.updateTrueCount(gameShoe.getDecksRemaining());
			player1.betHand(10);
			
			// Player plays turn
			while(player1Decision != stand) {
				if(player1Decision == hit)
					player1.drawCard(i, gameShoe.drawCard());

				if(player1Decision == split) {
					player1.splitHand(i);
					player1.drawCard(i, gameShoe.drawCard());
					player1.betHand(10);
				}
			player1Decision = player1.makeDecision(i, dealer1.getUpCardRank());
			}

			if(player1.getHandValue(i) > 21){
				std::cout << "Player busted" << "\n";
				player1.updateWallet(lose);
			}

		}

		// Dealer plays turn
		dealer1.drawCard(gameShoe.drawCard());
		Decisions dealer1Decision = dealer1.makeDecision();
		while(dealer1Decision != stand) {
			if(dealer1Decision == hit)
				dealer1.drawCard(gameShoe.drawCard());
			dealer1Decision = dealer1.makeDecision();
		}

		if(dealer1.getHandValue() > 21) {
			std::cout << "Dealer busted" << "\n";
			player1.updateWallet(win);
		}

		for(int i = 0; i < player1.getLastHandIdx() + 1; i ++) {
			if(player1.getHandValue(i) > dealer1.getHandValue()) {
				std::cout << "Player wins hand " << i << "\n";
				player1.updateWallet(win);
			}

			else if(player1.getHandValue(i) < dealer1.getHandValue()) {
				std::cout << "Player loses hand " << i << "\n";
				player1.updateWallet(lose);
			}

			else if(player1.getHandValue(i) == dealer1.getHandValue()){
				std::cout << "Hand is tied" << "\n";
				player1.updateWallet(push);
			}
		}
		
	}

	int asd;

	std::cin >> asd;

	return 0;
}