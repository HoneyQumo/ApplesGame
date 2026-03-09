#include <algorithm>
#include "Leaderboard.h"

namespace ApplesGame
{
    // void UpdateLeaderboard(std::vector<Leaderboard>& vector)
    // {
    //     std::stable_sort(std::begin(vector), std::end(vector), [](const Leaderboard& a, const Leaderboard& b)
    //     {
    //         return a.score > b.score;
    //     });
    // }
    //
    // void UpdatePlayerPosition(const int& newScore, const int& previousScore, std::vector<Leaderboard>& vector)
    // {
    //     if (previousScore > -1)
    //     {
    //         auto result = std::find_if(std::begin(vector), std::end(vector), [previousScore](const Leaderboard& item)
    //         {
    //             return item.score == previousScore;
    //         });
    //
    //         if (result != vector.end())
    //         {
    //             *result = {
    //                 "You",
    //                 newScore
    //             };
    //         }
    //     }
    //     else
    //     {
    //         vector.push_back({"You", newScore});
    //     }
    // }
}
