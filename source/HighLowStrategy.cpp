#include "HighLowStrategy.h"

HighLowStrategy::HighLowStrategy() {
    m_runningCount = 0;
    m_trueCount = 0;
}

void HighLowStrategy::updateRunningCount(Rank p_rank) {
    // Update running count based on drawn hand
    if(p_rank >= 2 && p_rank < 7) // Cards 2-6 are +1
        m_runningCount += 1;

    if(p_rank >= 10 || p_rank == ace) // Face cards and aces are -1
        m_runningCount -= 1;
    
    return;
}

void HighLowStrategy::updateTrueCount(int p_decksRemaining) {
    // Update true count based on decks remaining in the shoe
    m_trueCount = std::round(m_runningCount / p_decksRemaining);
    return;
}

int HighLowStrategy::getRunningCount() {
    return m_runningCount;
}

int HighLowStrategy::getTrueCount() {
    return m_trueCount;
}

void HighLowStrategy::resetCount() {
    m_runningCount = 0;
    m_trueCount = 0;
}