#include <functional>

#include <iostream>

#include "Common.h"
#include "CGame.h"

namespace odb {

    void CGame::tick( long ms ) {

    }

    CControlCallback CGame::getKeyPressedCallback() {
        return [&](ECommand command) {
            if ( command == ECommand::kLeft ) {
                std::cout << "left pressed" << std::endl;
            }
        };
    }

    CControlCallback CGame::getKeyReleasedCallback() {
        return [&](ECommand command) {
            if ( command == ECommand::kLeft ) {
                std::cout << "left released" << std::endl;
            }
        };
    }
}