//
// Created by monty on 27/08/16.
//

#ifndef BLANKSLATE_COMMON_H
#define BLANKSLATE_COMMON_H
namespace odb {
    enum class ECommand {
        kUp,
        kRight,
        kDown,
        kLeft,
        kFire1,
        kFire2
    };

    using CControlCallback = std::function< void(ECommand) >;
}
#endif //BLANKSLATE_COMMON_H
