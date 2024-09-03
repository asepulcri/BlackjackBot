//
// Created by Andrea on 11/06/2023.
//

#include "Card.h"
#include "HighLowStrategy.h"
#include "Shoe.h"
#include <vector>
#include <memory>
#include <iostream>

#pragma once

enum Decisions {
	hit,
	stand,
	doubledown,
	split,
	surrender
};

class Player {
	private:
		int m_lastHandIdx;
		int m_wallet;
		int m_bet;
		std::vector<int> m_handValue;
		std::vector<bool> m_softHand;
		std::vector<int> m_aces;
		std::vector<std::vector<std::unique_ptr<Card>>> m_hand;
		std::vector<int> m_betSpread;

	public:
		Player();

		// Actions
		void drawCard(int p_hand, std::unique_ptr<Card> p_card, std::unique_ptr<HighLowStrategy> p_hiLo);
		void addNewHand();
		void splitHand(int p_hand);
		int betHand(std::unique_ptr<HighLowStrategy> p_hiLo, int p_minimumBet);
		void resetHand();
		void updateWallet(bool p_win);
		
		// Getters
		int getHandValue(int p_hand);
		int getTrueCount(std::unique_ptr<HighLowStrategy> p_hiLo);
		int getLastHandIdx();
		
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
		void drawCard(std::unique_ptr<Card> p_card, std::unique_ptr<HighLowStrategy> p_hiLo);
		
		// Getters
		int getHandValue();
		Rank getUpCardRank();
		
		// Strategy
		Decisions makeDecision();
};