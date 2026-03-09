#pragma once
#include <string>
#include <vector>

namespace ApplesGame
{
    struct Leaderboard
    {
        std::string name;
        int score;
    };

    // int lastPlayerScore = -1;
    //
    // void UpdateLeaderboard(std::vector<Leaderboard>& vector);
    //
    // void UpdatePlayerPosition(const int& newScore, const int& previousScore, std::vector<Leaderboard>& vector);
}
