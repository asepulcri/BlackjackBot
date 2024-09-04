#include "Player.h"

// Player base class

// Constructor
Player::Player() {
    m_lastHandIdx = 0;
    m_aces = {0};
    m_handValue = {0};
    m_softHand = {false};
    m_wallet = 100;
    m_betSpread = {1, 2, 4, 7, 8, 10, 12};
    addNewHand();
}

// Basic actions
void Player::drawCard(int p_hand, std::unique_ptr<Card> p_card) {
    int cardValue = p_card->getRank();

    m_hiLo.updateRunningCount(static_cast<Rank> (cardValue));
	
    if(cardValue >= 10)
        cardValue = 10;
    
    else if(cardValue == ace) {
        m_softHand[p_hand] = true;
        m_aces[p_hand] ++;
        cardValue = 11;
    }

    m_handValue[p_hand] += cardValue;

    while(m_handValue[p_hand] > 21 && m_aces[p_hand] > 0) {
        m_handValue[p_hand] -= 10;
        m_aces[p_hand] --;
    }

    m_hand[p_hand].push_back(std::move(p_card));

    return;
};

void Player::addNewHand() {
    m_hand.emplace_back();
}

void Player::splitHand(int p_hand) {
    m_lastHandIdx ++;
    addNewHand();

    m_hand[m_lastHandIdx].push_back(std::move(m_hand[p_hand][1]));
    m_hand[p_hand].pop_back();
}

int Player::betHand(int p_minimumBet) {
    int trueCount = m_hiLo.getTrueCount();

    std::cout << "Runnning count is " << m_hiLo.getRunningCount() << "\n";
    
    if(trueCount < 0)
        m_bet += p_minimumBet;

    if(trueCount > 6)
        m_bet += p_minimumBet * m_betSpread.back();

    else
        m_bet += p_minimumBet * m_betSpread[trueCount];

    return m_bet;
}

void Player::updateWallet(Outcomes p_outcome) {
    if(win) {
        m_wallet += m_bet * 2;
    }

    if(lose) {
        m_wallet -= m_bet;
    }

    m_bet = 0;
}

void Player::updateRunningCountFromDealer(std::vector<std::unique_ptr<Card>> p_dealerHand) {
    std::vector<std::unique_ptr<Card>> dealerHand = std::move(p_dealerHand);

    for (auto& card: p_dealerHand) {
        Rank cardRank = card->getRank();
        m_hiLo.updateRunningCount(cardRank);
    }
}

void Player::updateTrueCount(Shoe p_shoe) {
    m_hiLo.updateTrueCount(p_shoe);
}

// Reset hand
void Player::resetHand() {
}

int Player::getHandValue(int p_hand) {
    return m_handValue[p_hand];
}

int Player::getLastHandIdx() {
    return m_lastHandIdx;
}

Decisions Player::makeDecision(int p_hand, Rank p_dealerUpCard) {
    if(m_handValue[p_hand] > 21)
        return stand;

    if(m_handValue[p_hand] == 21)
        return stand;

    if(m_hand[p_hand][0]->getRank() == m_hand[p_hand][1]->getRank() && m_hand.size() < 4) {
        Decisions splitDecision = pairSplittingDecisions(p_hand, p_dealerUpCard);

        if(splitDecision == split)
            return split;
        else
            return softTotalsDecisions(p_hand, p_dealerUpCard);
    }

    if(m_softHand[p_hand])
        return softTotalsDecisions(p_hand, p_dealerUpCard);

    return hardTotalsDecisions(p_hand, p_dealerUpCard);
};

Decisions Player::hardTotalsDecisions(int p_hand, Rank p_dealerUpCard) {
    if (m_handValue[p_hand] < 8)
        return hit;

    if (m_handValue[p_hand] > 17)
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

    int totalIndex = m_handValue[p_hand] - int(8);

    int dealerIndex = p_dealerUpCard < 10 ? p_dealerUpCard != ace ? p_dealerUpCard - int(2) : int(9) : int(8);

    int decisionToMake = arr[totalIndex][dealerIndex];

    return static_cast<Decisions>(decisionToMake);
}

Decisions Player::softTotalsDecisions(int p_hand, Rank p_dealerUpCard) {

    int arr[8][10] = {
        {0, 0, 0, 2, 2, 0, 0, 0, 0, 0},
        {0, 0, 0, 2, 2, 0, 0, 0, 0, 0},
        {0, 0, 2, 2, 2, 0, 0, 0, 0, 0},
        {0, 0, 2, 2, 2, 0, 0, 0, 0, 0},
        {0, 2, 2, 2, 2, 0, 0, 0, 0, 0},
        {2, 2, 2, 2, 2, 1, 1, 0, 0, 0},
        {1, 1, 1, 1, 2, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

    int totalIndex = m_handValue[p_hand] - int(13);

    int dealerIndex = p_dealerUpCard < 10 ? p_dealerUpCard != ace ? p_dealerUpCard - int(2) : int(9) : int(8);

    int decisionToMake = arr[totalIndex][dealerIndex];

    return static_cast<Decisions>(decisionToMake);
}

Decisions Player::pairSplittingDecisions(int p_hand, Rank p_dealerUpCard) {
    int arr[10][10] = {
        {3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
        {1, 3, 3, 3, 3, 3, 3, 1, 1, 1},
        {1, 3, 3, 3, 3, 3, 3, 1, 1, 1},
        {1, 1, 1, 1, 3, 3, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 3, 3, 3, 3, 3, 1, 1, 1, 1},
        {1, 3, 3, 3, 3, 3, 3, 1, 1, 1},
        {3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
        {1, 3, 3, 3, 3, 3, 1, 3, 3, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

    int rankCard = m_hand[p_hand][0]->getRank();

    int totalIndex = rankCard < 10 ? rankCard - 1 : int(9);

    int dealerIndex = p_dealerUpCard < 10 ? p_dealerUpCard - 1 : int(9);

    int decisionToMake = arr[totalIndex][dealerIndex];

    return static_cast<Decisions>(decisionToMake);
}

Dealer::Dealer() {
}

Decisions Dealer::makeDecision() {
    if(m_handValue < 17)
        return hit;

    return stand;
}

void Dealer::drawCard(std::unique_ptr<Card> p_card) {
    int cardValue = p_card->getRank();

    std::cout << "Dealer drew " << p_card->getRank() << " of " << p_card->getSuit();

    if(m_handValue = 0) {
        m_upCardRank = static_cast<Rank> (cardValue);
    }
	
    if(cardValue >= 10)
        cardValue = 10;
    
    else if(cardValue == ace) {
        m_softHand = true;
        m_aces ++;
        cardValue = 11;
    }

    m_handValue += cardValue;

    while(m_handValue > 21 && m_aces > 0) {
        m_handValue -= 10;
        m_aces --;
    }

    m_hand.push_back(std::move(p_card));
    
    return;
}

int Dealer::getHandValue() {
    return m_handValue;
}

Rank Dealer::getUpCardRank() {
    return m_upCardRank;
}

std::vector<std::unique_ptr<Card>> Dealer::getHand() {
    return std::move(m_hand);
}