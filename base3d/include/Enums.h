#ifndef ENUMS_H
#define ENUMS_H


enum ECommand {
    kCommandNone,
    kCommandUp,
    kCommandRight,
    kCommandDown,
    kCommandLeft,
    kCommandFire1,
    kCommandFire2,
    kCommandBack,
    kCommandQuit,
    kCommandStrafeLeft,
    kCommandStrafeRight,
    kCommandFire3,
    kCommandFire4
};

enum EGameMenuState {
    kMainMenu,
    kHelp,
    kCredits,
    kQuit,
    kInterrogate_Sofia
};

enum EPresentationState {
    kAppearing,
    kWaitingForInput,
    kConfirmInputBlink1,
    kConfirmInputBlink2,
    kConfirmInputBlink3,
    kConfirmInputBlink4,
    kConfirmInputBlink5,
    kConfirmInputBlink6,
    kFade
};
#endif
