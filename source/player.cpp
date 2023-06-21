#include "../include/player.h"

players::player::player() : m_handValue(int(0)) {
};

int players::player::getHandValue() {
	return m_handValue;
};

void players::player::drawCard(std::unique_ptr<cards::card> p_card) {
	m_hand.push_back(std::move(p_card));
};