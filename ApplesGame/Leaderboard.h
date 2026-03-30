#pragma once
#include <map>
#include <string>
#include <vector>

namespace ApplesGame
{
    using LeaderboardMap = std::map<std::string, unsigned int>;
    using LeaderboardPositionPair = std::pair<std::string, unsigned int>;

    std::vector<LeaderboardPositionPair> GetSortedLeaderboardArray(const LeaderboardMap& leaderboard);

    void UpdatePlayerPosition(const unsigned int& newScore, const std::string& playerName, LeaderboardMap& leaderboard);
}
