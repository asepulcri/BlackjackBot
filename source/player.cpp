#include "../include/player.h"
#include <iostream>

// Player base class
players::person::person() : m_softHand(false), m_handValue(int(0)) {};

int players::person::getHandValue() {
    calculateHandValue();
	return m_handValue;
};

void players::person::calculateHandValue() {
    int value = 0;
    int aces = 0;
    for (const auto& card : m_hand) {
        int cardValue = card->getRank();
        if (cardValue >= 10) {
            cardValue = 10;
        }
        else if (cardValue == cards::ace) {
            aces++;
            cardValue = 11;
        }
        value += cardValue;
    }

    m_softHand = aces > 0;

    while (value > 21 && aces > 0) {
        value -= 10;
        aces--;
    }

    m_handValue = value;
}

void players::person::drawCard(std::unique_ptr<cards::card> p_card) {
	m_hand.push_back(std::move(p_card));
};

players::player::player(int p_buyIn) : m_wallet(p_buyIn) {};

void players::player::showHand() {
    if (m_hand.empty())
        return;

    for (int i = 0; i < m_hand.size(); i++) {
        std::cout << cards::rankNames[(m_hand[i]->getRank())] << " of " << cards::suitNames[(m_hand[i]->getSuit())] << std::endl;
    }
}

int players::player::getWalletValue() {
    return m_wallet;
}

void players::player::betHand(int p_betValue) {
    m_wallet -= p_betValue;
    return;
}

players::Decisions players::player::makeDecision(cards::card p_dealerUpCard) {
    if (m_softHand)
        return softTotalsDecisions(p_dealerUpCard);

    return hardTotalsDecisions(p_dealerUpCard);
}

players::Decisions players::player::hardTotalsDecisions(cards::card p_dealerUpCard) {
    if (m_handValue < 8)
        return players::Decisions::hit;

    if (m_handValue > 17)
        return players::Decisions::stand;
    
    int arr[10][10] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 2, 2, 2, 2, 0, 0, 0, 0, 0},
        {2, 2, 2, 2, 2, 2, 2, 2, 0, 0},
        {2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
        {0, 0, 1, 1, 1, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1} };

    int totalIndex = m_handValue - int(8);

    int dealerIndex = p_dealerUpCard.getRank() < 10 ? p_dealerUpCard.getRank() != cards::Rank::ace ? p_dealerUpCard.getRank() - int(2) : int(9) : int(8);

    int decisionToMake = arr[totalIndex][dealerIndex];

    return static_cast<players::Decisions>(decisionToMake);
}

players::Decisions players::player::softTotalsDecisions(cards::card p_dealerUpCard) {

    int arr[8][10] = {
        {0, 0, 0, 2, 2, 0, 0, 0, 0, 0},
        {0, 0, 0, 2, 2, 0, 0, 0, 0, 0},
        {0, 0, 2, 2, 2, 0, 0, 0, 0, 0},
        {0, 0, 2, 2, 2, 0, 0, 0, 0, 0},
        {0, 2, 2, 2, 2, 0, 0, 0, 0, 0},
        {2, 2, 2, 2, 2, 1, 1, 0, 0, 0},
        {1, 1, 1, 1, 2, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

    int totalIndex = m_handValue - int(13);

    int dealerIndex = p_dealerUpCard.getRank() < 10 ? p_dealerUpCard.getRank() != cards::Rank::ace ? p_dealerUpCard.getRank() - int(2) : int(9) : int(8);

    int decisionToMake = arr[totalIndex][dealerIndex];

    return static_cast<players::Decisions>(decisionToMake);
}

players::Decisions players::player::pairSplittingDecisions(cards::card p_dealerUpCard) {
    if (m_handValue < 8)
        return players::Decisions::hit;

    if (m_handValue > 17)
        return players::Decisions::stand;

    int arr[10][10] = {
        {3, 3, 3, 3, 3, 3, 1, 1, 1, 1},
        {3, 3, 3, 3, 3, 3, 1, 1, 1, 1},
        {1, 1, 1, 3, 3, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {3, 3, 3, 3, 3, 1, 1, 1, 1, 1},
        {3, 3, 3, 3, 3, 3, 1, 1, 1, 1},
        {3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
        {3, 3, 3, 3, 3, 1, 3, 3, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {3, 3, 3, 3, 3, 3, 3, 3, 3, 3}};

    int totalIndex = m_handValue / int(2) - int(2);

    int dealerIndex = p_dealerUpCard.getRank() < 10 ? p_dealerUpCard.getRank() != cards::Rank::ace ? p_dealerUpCard.getRank() - int(2) : int(9) : int(8);

    int decisionToMake = arr[totalIndex][dealerIndex];

    return static_cast<players::Decisions>(decisionToMake);
}

// Dealer Class
players::dealer::dealer() : m_faceUpCard(cards::card(cards::Suit(cards::clubs), cards::Rank(cards::ace))), m_revealHand(bool(false)) {};

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
    if (m_revealHand) {
        calculateHandValue();
		return m_handValue;
    }

	return -1;
}

players::Decisions players::dealer::makeDecision() {
    calculateHandValue();
    if (m_handValue <= 17 && m_softHand == true)
        return players::Decisions::hit;

    return players::Decisions::stand;
}

void players::dealer::showFaceUpCard() {
    std::cout << cards::rankNames[(m_faceUpCard.getRank())] << " of " << cards::suitNames[(m_faceUpCard.getSuit())] << std::endl;
}