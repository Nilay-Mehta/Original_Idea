#pragma once

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <map>
#include <string>

namespace input {
    enum class Action {
        MoveUp,
        MoveDown,
        MoveLeft,
        MoveRight,
        Shoot
    };


    enum class InputType {
        Keyboard,
        Mouse
    };

    struct InputBinding {
        sf::Keyboard::Key key;
        sf::Mouse::Button button;
        InputType type;

        InputBinding() :
            key(sf::Keyboard::Unknown), button(sf::Mouse::ButtonCount), type(InputType::Keyboard) {}

        InputBinding(sf::Keyboard::Key k) :
            key(k), button(sf::Mouse::ButtonCount), type(InputType::Keyboard) {}

        InputBinding(sf::Mouse::Button b) :
            key(sf::Keyboard::Unknown), button(b), type(InputType::Mouse) {}
    };

    class KeyBindings {
    public:
        KeyBindings();//default keybindings
        void bind(Action action, InputBinding input);
        InputBinding getBinding(Action action) const;
        void loadFromFile(std::string filename);
        void saveToFile(std::string filename);
        bool isKeyPressed(Action action) const;


    private:
        std::map<Action, InputBinding> keyBindings;
    };
}