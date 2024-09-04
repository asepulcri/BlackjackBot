#include "HighLowStrategy.h"

HighLowStrategy::HighLowStrategy() {
    m_runningCount = 0;
    m_trueCount = 0;
}

void HighLowStrategy::updateRunningCount(Rank p_rank) {
    if(p_rank >= 2 && p_rank < 7)
        m_runningCount += 1;

    if(p_rank >= 10 || p_rank == ace)
        m_runningCount -= 1;
    
    return;
}

void HighLowStrategy::updateTrueCount(Shoe p_shoe) {
    int decksRemaining = p_shoe.getDecksRemaining();
    m_trueCount = std::round(m_runningCount / decksRemaining);

    return;
}

int HighLowStrategy::getRunningCount() {
    return m_runningCount;
}

int HighLowStrategy::getTrueCount() {
    return m_trueCount;
}