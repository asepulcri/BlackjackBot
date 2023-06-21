//
// Created by Andrea on 11/06/2023.
//

#include "card.h"
#include "shoe.h"
#include <vector>

#pragma once

namespace players {
	class player {
	protected:
		std::vector<std::unique_ptr<cards::card>> m_hand;
		int m_handValue;

	public:
		player();

		int getHandValue();
		void drawCard(std::unique_ptr<cards::card> p_card);
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
	};
}