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
	protected:
		int m_splits;
		std::vector<int> m_handValue;
		std::vector<bool> m_softHand;
		std::vector<int> m_aces;
		std::vector<std::vector<std::unique_ptr<Card>>> m_hand;

	public:
		Player();

		void drawCard(int p_hand, std::unique_ptr<Card> p_card);
		int getHandValue(int p_hand);
		Decisions makeDecision(int p_hand, Rank p_dealerUpCard);

		Decisions hardTotalsDecisions(int p_hand, Rank p_dealerUpCard);
		Decisions softTotalsDecisions(int p_hand, Rank p_dealerUpCard);
		Decisions pairSplittingDecisions(int p_hand, Rank p_dealerUpCard);
};

// class Dealer : public Player {
// 	private:
// 		Rank m_upCardRank;

// 	public:
// 		Dealer();

// 		Decisions makeDecision();
// 		void checkUpCard();
// 		Rank getUpCard();
// };