#include "Player.h"

// Player base class

Player::Player() {
    m_lastHandIdx = 0;
    m_aces = {0};
    m_handValue = {0};
    m_softHand = {false};
    m_wallet = 100;
    m_bet = 0;
    m_betSpread = {1, 2, 4, 7, 8, 10, 12};
    addNewHand();
}

void Player::drawCard(int p_hand, std::unique_ptr<Card> p_card) {
    int cardValue = p_card->getRank();

    std::cout << "Player draws " << std::map<p_card->getRank(), Rank> << " of " << std::map<p_card->getSuit(),><< "\n";

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

void Player::betHand(int p_minimumBet) {
    int trueCount = m_hiLo.getTrueCount();

    if(trueCount < 0) {
        m_bet += p_minimumBet;
    }

    if(trueCount > 6) {
        m_bet += p_minimumBet * m_betSpread.back();
    }

    else {
        m_bet += p_minimumBet * m_betSpread[trueCount];
    }
}

void Player::updateWallet(Outcomes p_outcome) {
    if(win) {
        m_wallet += 2 * m_bet;
    }

    if(lose) {
        m_wallet -= m_bet;
    }

    if(push) {
        ;
    }

    m_bet = 0;

    return;
}

void Player::updateTrueCount(int p_decksRemaining) {
    m_hiLo.updateTrueCount(p_decksRemaining);
    return;
}

int Player::getHandValue(int p_hand) {
    return m_handValue[p_hand];
}

int Player::getLastHandIdx() {
    return m_lastHandIdx;
}

int Player::getBet() {
    return m_bet;
}

Decisions Player::makeDecision(int p_hand, Rank p_dealerUpCard) {
    Decisions playerDecision;
    if(m_handValue[p_hand] > 21)
        playerDecision = stand;

    if(m_handValue[p_hand] == 21)
        playerDecision = stand;

    if(m_hand[p_hand][0]->getRank() == m_hand[p_hand][1]->getRank() && m_hand.size() < 4) {
        Decisions splitDecision = pairSplittingDecisions(p_hand, p_dealerUpCard);

        if(splitDecision == split)
            playerDecision = split;
        else
            playerDecision = softTotalsDecisions(p_hand, p_dealerUpCard);
    }

    if(m_softHand[p_hand])
        playerDecision = softTotalsDecisions(p_hand, p_dealerUpCard);

    playerDecision = hardTotalsDecisions(p_hand, p_dealerUpCard);

    std::cout << static_cast<Decisions> (playerDecision) << "\n";

    return playerDecision;
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
        {0, 0, 0, 1, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 0, 0, 0, 0, 0},
        {0, 0, 1, 1, 1, 0, 0, 0, 0, 0},
        {0, 0, 1, 1, 1, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 1, 0, 0, 0},
        {1, 1, 1, 1, 0, 1, 1, 1, 1, 1},
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
    m_handValue = 0;
    m_softHand = false;
    m_aces = 0;
};

Decisions Dealer::makeDecision() {
    Decisions dealerDecision;

    if(m_handValue < 17)
        dealerDecision = hit;

    dealerDecision = stand;

    std::cout << static_cast<Decisions> (dealerDecision);

    return dealerDecision;
};

void Dealer::drawCard(std::unique_ptr<Card> p_card) {
    int cardValue = p_card->getRank();

    std::cout << "Dealer draws " << std::map<Rank, > (p_card->getRank()) << " of " << static_cast<Suit> (p_card->getSuit()) << "\n";

    if(m_hand.empty()) {
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
};

int Dealer::getHandValue() {
    return m_handValue;
}

Rank Dealer::getUpCardRank() {
    return m_upCardRank;
}