//
// Created by nilay on 19-06-2025.
//

#include "keybindings.h"
#include <fstream>
#include <stdexcept>

using namespace input;

KeyBindings::KeyBindings() {
    bind(Action::MoveUp, sf::Keyboard::W);
    bind(Action::MoveDown, sf::Keyboard::S);
    bind(Action::MoveLeft, sf::Keyboard::A);
    bind(Action::MoveRight, sf::Keyboard::D);
    bind(Action::Shoot, sf::Mouse::Left);
}

void KeyBindings::bind(Action action, InputBinding input) {
    keyBindings[action] = input;
}

InputBinding KeyBindings::getBinding(Action action) const {
    return keyBindings.at(action);
}

bool KeyBindings::isKeyPressed(Action action) const {
    auto binding = getBinding(action);
    if (binding.type == InputType::Keyboard)
        return sf::Keyboard::isKeyPressed(binding.key);
    else if (binding.type == InputType::Mouse)
        return sf::Mouse::isButtonPressed(binding.button);
    return false;
}

