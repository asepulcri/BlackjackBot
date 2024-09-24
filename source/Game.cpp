#include "Game.h"

void Game::playGame() {

    Shoe gameShoe(6);
    Player player1;
    Dealer dealer1;

    Outcomes player1Outcome(undetermined);

	while(gameShoe.getDecksRemaining() > 1.5){
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
				player1Outcome = lose;
			}

		}

        if(player1Outcome != lose) {
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
                player1Outcome = win;
            }

            for(int i = 0; i < player1.getLastHandIdx() + 1; i ++) {
                if(player1.getHandValue(i) > dealer1.getHandValue()) {
                    std::cout << "Player wins hand " << i << "\n";
                    player1Outcome = win;
                }

                else if(player1.getHandValue(i) < dealer1.getHandValue()) {
                    std::cout << "Player loses hand " << i << "\n";
                    player1Outcome = lose;
                }

                else if(player1.getHandValue(i) == dealer1.getHandValue()){
                    std::cout << "Hand is tied" << "\n";
                    player1Outcome = push;
                }

            }       
        }
        player1.updateWallet(player1Outcome);

        // resetHands(player1, dealer1, player1Outcome);

        player1Outcome = undetermined;
        player1.resetHands();
        dealer1.resetHands();
	}

    return;
}

void Game::resetHands(Player p_player, Dealer p_dealer, Outcomes p_playerOutcome) {
    // p_playerOutcome = undetermined;
    // p_player.resetHands();
    // p_dealer.resetHands();
    // return;
}