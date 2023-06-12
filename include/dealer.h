//
// Created by Andrea on 11/06/2023.
//

#include "card.h"
#include <vector>

namespace dealer {
	class dealer {
	private:
		std::vector<card::card> m_hand;
	public:
		dealer() {}

		void dealCards() {

		}

		std::vector<card::card> getHand() {
			return m_hand;
		}
	};
}