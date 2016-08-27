#include <functional>
#include <memory>
#include <iostream>
#include "Common.h"
#include "CGame.h"
#include "CRenderer.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/html5.h>

#endif

std::shared_ptr<odb::CRenderer> renderer;
odb::CGame game;

void gameLoopTick() {
    renderer->render( 33 );
    renderer->handleSystemEvents();
    game.tick( 33 );
}


int main() {
    renderer = std::make_shared<odb::CRenderer>( game.getKeyPressedCallback(), game.getKeyReleasedCallback() );

#ifdef __EMSCRIPTEN__
    //  emscripten_request_fullscreen(0, 1);
  emscripten_set_main_loop( gameLoopTick, 30, 1 );
#else
    while ( true ) {
        gameLoopTick();
        renderer->sleep( 33 );
    }
#endif
    return 0;
}