#include "../include/player.h"

players::player::player() : m_handValue(int(0)) {
};

int players::player::getHandValue() {
	return m_handValue;
};

void players::player::drawCard(std::unique_ptr<cards::card> p_card) {
	m_hand.push_back(std::move(p_card));
};

players::dealer::dealer() : m_faceUpCard(cards::card(cards::Suit(cards::clubs), cards::Rank(cards::ace))), m_revealHand(bool(false)) {
};

void players::dealer::revealHand() {
	m_revealHand = true;
}

cards::card players::dealer::getFaceUpCard() {
	return m_faceUpCard;
}

void players::dealer::drawCard(std::unique_ptr<cards::card> p_card) {
	if (m_hand.empty())
		m_faceUpCard = *p_card;

	m_hand.push_back(std::move(p_card));
};

int players::dealer::getHandValue() {
	if (m_revealHand)
		return m_handValue;

	return -1;
}