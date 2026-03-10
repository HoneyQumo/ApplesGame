#pragma once
#include <string>
#include <vector>

namespace ApplesGame
{
    struct Leaderboard
    {
        std::string name;
        unsigned int score;
    };

    void UpdateLeaderboard(std::vector<Leaderboard>& vector);

    void UpdatePlayerPosition(const unsigned int& newScore, const std::string& playerName, std::vector<Leaderboard>& vector);
}
