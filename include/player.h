//
// Created by Andrea on 11/06/2023.
//

#include "card.h"
#include "shoe.h"
#include <vector>

#pragma once

namespace players {
	class player {
	private:
		std::vector<std::unique_ptr<cards::card>> m_hand;
		int m_handValue;

	public:
		player();

		int getHandValue();
		void drawCard(std::unique_ptr<cards::card > p_card);
	};


	//class dealer : player {
	//private:
	//	card::card m_faceUpCard;

	//public:
	//	dealer() {}
	//};
}