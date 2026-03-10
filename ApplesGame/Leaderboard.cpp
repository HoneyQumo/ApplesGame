#include <algorithm>
#include "Leaderboard.h"

namespace ApplesGame
{
    std::vector<LeaderboardPositionPair> GetSortedLeaderboardArray(const LeaderboardMap& leaderboard)
    {
        std::vector<LeaderboardPositionPair> tmpArray(leaderboard.begin(), leaderboard.end());

        std::stable_sort(std::begin(tmpArray), std::end(tmpArray), [](const LeaderboardPositionPair& a, const LeaderboardPositionPair& b)
        {
            return a.second > b.second;
        });

        return tmpArray;
    }

    void UpdatePlayerPosition(const unsigned int& newScore, const std::string& playerName, LeaderboardMap& leaderboard)
    {
        unsigned int previousPlayerScore = leaderboard[playerName];

        leaderboard[playerName] = std::max(newScore, previousPlayerScore);
    }
}
