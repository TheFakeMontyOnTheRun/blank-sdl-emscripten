#ifndef CGAME_H
#define CGAME_H

namespace odb {
    class CGame {
    private:

    public:
        void tick( long ms );
        CControlCallback getKeyPressedCallback();
        CControlCallback getKeyReleasedCallback();
    };
}
#endif