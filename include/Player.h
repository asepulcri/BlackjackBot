//
// Created by Andrea on 11/06/2023.
//

#include "Card.h"
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
		std::vector<int> m_handValue;
		std::vector<bool> m_softHand;
		std::vector<int> m_aces;
		std::vector<int> m_bets;
		std::vector<std::vector<std::unique_ptr<Card>>> m_hand;

	public:
		Player();

		// Actions
		void drawCard(int p_hand, std::unique_ptr<Card> p_card);
		void addNewHand();
		void splitHand(int p_hand);
		void betHand(int p_hand, int p_bet);
		void resetHand();
		
		// Getters
		int getHandValue(int p_hand);
		
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
		
		// Getters
		int getHandValue();
		Rank getUpCardRank();
		
		// Strategy
		Decisions makeDecision();
};