#include <vector>

struct handStats {
    int runningCount;
    int trueCount;
    int walletValue;
};

class GameStats {
    public:
        GameStats();

        std::vector<int> m_runningCountHistory;
        std::vector<int> m_trueCountHistory;  
        std::vector<int> m_walletHistory;
        handStats m_handStats;
        
        // Actions
        void updateHandStats(int p_runningCount, int p_trueCount, int p_walletValue);
};