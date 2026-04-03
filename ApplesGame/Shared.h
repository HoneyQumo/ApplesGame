#pragma once
#include "SFML/Graphics.hpp"

namespace ApplesGame
{
    enum class MenuDirectionMovement
    {
        Up = 0,
        Down,
    };

    struct MenuOption
    {
        std::string title;
        sf::Text textNode;
    };

    struct Game;

    template <typename T>
    void MenuToggleOption(std::map<T, MenuOption>& options, T& selectedOptionKey, MenuDirectionMovement direction)
    {
        if (options.empty()) return;

        const auto it = options.find(selectedOptionKey);
        if (it == options.end()) return;

        if (direction == MenuDirectionMovement::Up)
        {
            if (it == options.begin())
            {
                auto prevIt = std::prev(options.end());
                selectedOptionKey = prevIt->first;
                prevIt->second.textNode.setFillColor(sf::Color::Green);
            }
            else
            {
                auto prevIt = std::prev(it);
                selectedOptionKey = prevIt->first;
                prevIt->second.textNode.setFillColor(sf::Color::Green);
            }
        }
        else if (direction == MenuDirectionMovement::Down)
        {
            const auto nextIt = std::next(it);
            if (nextIt == options.end())
            {
                auto nextIt = options.begin();
                selectedOptionKey = nextIt->first;
                nextIt->second.textNode.setFillColor(sf::Color::Green);
            }
            else
            {
                selectedOptionKey = nextIt->first;
                nextIt->second.textNode.setFillColor(sf::Color::Green);
            }
        }

        it->second.textNode.setFillColor(sf::Color::White);
    }
}
