#include <algorithm>
#include "Leaderboard.h"

namespace ApplesGame
{
    void UpdateLeaderboard(std::vector<Leaderboard>& vector)
    {
        std::stable_sort(std::begin(vector), std::end(vector), [](const Leaderboard& a, const Leaderboard& b)
        {
            return a.score > b.score;
        });
    }

    void UpdatePlayerPosition(const unsigned int& newScore, const std::string& playerName, std::vector<Leaderboard>& vector)
    {
        auto result = std::find_if(std::begin(vector), std::end(vector), [playerName](const Leaderboard& item)
        {
            return item.name == playerName;
        });

        if (result != vector.end())
        {
            result->score = std::max(newScore, result->score);
        }
        else
        {
            vector.push_back({playerName, newScore});
        }
    }
}
