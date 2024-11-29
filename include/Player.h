//
// Created by Andrea on 11/06/2023.
//

#include "Card.h"
#include "EnumNames.h"
#include "HighLowStrategy.h"
#include "PrintStrings.h"
#include "Shoe.h"
#include <vector>
#include <memory>
#include <iostream>

#pragma once

class Player {
	private:
		int m_lastHandIdx;
		int m_bet;
		int m_wallet;
		HighLowStrategy m_hiLo;
		std::vector<int> m_handValue;
		std::vector<bool> m_softHand;
		std::vector<int> m_aces;
		std::vector<std::vector<std::unique_ptr<Card>>> m_hand;
		std::vector<int> m_betSpread;

	public:
		Player();

		// Actions
		void drawCard(int p_hand, std::unique_ptr<Card> p_card);
		void addNewHand();
		void splitHand(int p_hand);
		void betHand(int p_minimumBet);
		void updateWallet(Outcomes p_outcome);
		void updateTrueCount(int p_decksRemaining);
		void resetHands();
		void resetCount();
		
		// Getters
		int getHandValue(int p_hand);
		int getLastHandIdx();
		int getBet();
		int getRunningCount();
		int getTrueCount();
		int getWalletAmount();
		
		// Basic strategy
		Decisions makeDecision(int p_hand, Rank p_dealerUpCard);
		Decisions hardTotalsDecisions(int p_hand, Rank p_dealerUpCard);
		Decisions softTotalsDecisions(int p_hand, Rank p_dealerUpCard);
		Decisions pairSplittingDecisions(int p_hand, Rank p_dealerUpCard);
};

class Dealer {
	private:
		Rank m_upCardRank;
		int m_handValue;
		bool m_softHand;
		int m_aces;
		std::vector<std::unique_ptr<Card>> m_hand;

	public:
		Dealer ();

		// Actions
		void drawCard(std::unique_ptr<Card> p_card);
		void resetHands();
		
		// Getters
		int getHandValue();
		Rank getUpCardRank();
		std::vector<std::unique_ptr<Card>> getHand();
		
		// Strategy
		Decisions makeDecision();
};