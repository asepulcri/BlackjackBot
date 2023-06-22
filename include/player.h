//
// Created by Andrea on 11/06/2023.
//

#include "card.h"
#include "shoe.h"
#include <vector>

#pragma once

namespace players {

	enum Decisions {
		hit,
		stand,
		doubledown,
		split,
		surrender
	};

	class player {
	protected:
		std::vector<std::unique_ptr<cards::card>> m_hand;
		int m_handValue;
		bool m_softHand;

	public:
		player();

		int getHandValue();
		void calculateHandValue();
		void drawCard(std::unique_ptr<cards::card> p_card);

		Decisions makeDecision(cards::card p_dealerUpCard);
		Decisions hardTotalsDecisions(cards::card p_dealerUpCard);
		Decisions softTotalsDecisions(cards::card p_dealerUpCard);
		Decisions pairSplittingDecisions(cards::card p_dealerUpCard);
	};


	class dealer : public player {
	private:
		cards::card m_faceUpCard;
		bool m_revealHand;

	public:
		dealer();

		void revealHand();
		void drawCard(std::unique_ptr<cards::card> p_card);
		int getHandValue();
		cards::card getFaceUpCard();

		Decisions makeDecision();
	};
}