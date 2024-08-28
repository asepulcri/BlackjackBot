#include "Player.h"

// Player base class
Player::Player() {};

void Player::Player::showHand() {
    if (m_hand.empty())
        return;

    for (int i = 0; i < m_hand.size(); i++) {
        std::cout << rankNames[(m_hand[i]->getRank() - int(1))] << " of " << suitNames[(m_hand[i]->getSuit())] << std::endl;
    }
    return;
}

void Player::showLastDrawnCard() {
    if (m_hand.empty())
        return;

    std::cout << rankNames[(m_hand.back()->getRank() - int(1))] << " of " << suitNames[(m_hand.back()->getSuit())] << std::endl;

    return;
}

int Player::getHandValue() {
    calculateHandValue();
	return m_handValue;
};

void Player::calculateHandValue() {
    int value = 0;
    int aces = 0;
    for (const auto& card : m_hand) {
        int cardValue = card->getRank();
        if (cardValue >= 10) {
            cardValue = 10;
        }
        else if (cardValue == ace) {
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
    return;
}

void Player::drawCard(std::unique_ptr<Card> p_card) {
	m_hand.push_back(std::move(p_card));
    return;
};

void Player::clearHand() {
    m_hand.clear();
    return;
}


Decisions Player::makeDecision(Card p_dealerUpCard) {
    calculateHandValue();

    if (m_handValue > int(21))
        return stand;

    if (m_handValue == int(21))
        return stand;

    if (m_softHand)
        return softTotalsDecisions(p_dealerUpCard);

    return hardTotalsDecisions(p_dealerUpCard);
}

Decisions Player::hardTotalsDecisions(Card p_dealerUpCard) {
    if (m_handValue < 8)
        return hit;

    if (m_handValue > 17)
        return stand;
    
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

    return static_cast<Decisions>(decisionToMake);
}

Decisions Player::softTotalsDecisions(Card p_dealerUpCard) {

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

    int dealerIndex = p_dealerUpCard.getRank() < 10 ? p_dealerUpCard.getRank() != ace ? p_dealerUpCard.getRank() - int(2) : int(9) : int(8);

    int decisionToMake = arr[totalIndex][dealerIndex];

    return static_cast<Decisions>(decisionToMake);
}

Decisions Player::pairSplittingDecisions(Card p_dealerUpCard) {
    if (m_handValue < 8)
        return hit;

    if (m_handValue > 17)
        return stand;

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

    return static_cast<Decisions>(decisionToMake);
}

// Dealer Class
Dealer() : m_revealHand(bool(false)) {};

void Dealer::revealHand() {
	m_revealHand = true;
    return;
}

Card Dealer::getFaceUpCard() {
	return m_faceUpCard;
}

void Dealer::drawCard(std::unique_ptr<Card> p_card) {
	if (m_hand.empty())
		m_faceUpCard = *p_card;

	m_hand.push_back(std::move(p_card));
    return;
};

int Dealer::getHandValue() {
    if (m_revealHand) {
        calculateHandValue();
		return m_handValue;
    }

	return -1;
}

Decisions Dealer::makeDecision() {
    calculateHandValue();
    if (m_handValue <= 17 || (m_handValue == int(17) && m_softHand == true))
        return hit;

    return stand;
}

void Dealer::showFaceUpCard() {
    std::cout << rankNames[(m_faceUpCard.getRank() - int(1))] << " of " << suitNames[(m_faceUpCard.getSuit())] << std::endl;
    return;
}