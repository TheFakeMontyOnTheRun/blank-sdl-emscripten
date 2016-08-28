#ifndef IRENDERER_H
#define IRENDERER_H

#include "CGameSnapshot.h"

namespace odb {



    class CRenderer {
    private:
        CControlCallback mOnKeyPressedCallback;
        CControlCallback mOnKeyReleasedCallback;
        CGameSnapshot mGameSnapshot;
     public:
        CRenderer( CControlCallback keyPressedCallback, CControlCallback keyReleasedCallback );
        void render( long ms );
        void handleSystemEvents();
        void sleep( long ms );
        void setSnapshot( const CGameSnapshot& snapshot );
    };
}
#endif