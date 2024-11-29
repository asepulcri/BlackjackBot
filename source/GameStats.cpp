#include "GameStats.h"

GameStats::GameStats() {
};

void GameStats::updateHandStats(int p_runningCount, int p_trueCount, int p_walletValue) {
    m_handStats.runningCount = p_runningCount;
    m_handStats.trueCount = p_trueCount;
    m_handStats.walletValue = p_walletValue;

    m_runningCountHistory.push_back(m_handStats.runningCount);
    m_trueCountHistory.push_back(m_handStats.trueCount);
    m_walletHistory.push_back(m_handStats.walletValue);
};