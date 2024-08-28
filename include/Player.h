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
		int m_handValue;
		bool m_softHand;
		int m_aces;
		std::vector<std::unique_ptr<Card>> m_hand;

	public:
		Player();

		void drawCard(std::unique_ptr<Card> p_card);
		int getHandValue();
		Decisions makeDecision(Rank p_dealerUpCard);

		Decisions hardTotalsDecisions(Rank p_dealerUpCard);
		Decisions softTotalsDecisions(Rank p_dealerUpCard);
		Decisions pairSplittingDecisions(Rank p_dealerUpCard);
};

class Dealer : public Player {
	private:
		Rank m_upCardRank;

	public:
		Dealer();

		Decisions makeDecision();
		void checkUpCard();
		Rank getUpCard();
};