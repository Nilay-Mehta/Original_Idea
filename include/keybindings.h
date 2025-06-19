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
        InputType type;
        union {
            sf::Keyboard::Key key;
            sf::Mouse::Button button;
        };

        InputBinding(sf::Keyboard::Key k) :
        type(InputType::Keyboard), key(k) {}

        InputBinding(sf::Mouse::Button b) :
        type(InputType::Mouse), button(b) {}
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
