#include <utility>
#include <functional>
#include <array>
#include <vector>

#include "Common.h"
#include "CRenderer.h"

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

namespace odb {

    SDL_Surface *video;

    CRenderer::CRenderer( CControlCallback keyPressedCallback, CControlCallback keyReleasedCallback ):
    mOnKeyPressedCallback( keyPressedCallback ), mOnKeyReleasedCallback( keyReleasedCallback )
    {
        SDL_Init( SDL_INIT_EVERYTHING );
        video = SDL_SetVideoMode( 640, 480, 0, 0 );
    }

    void CRenderer::setSnapshot( const CGameSnapshot& snapshot ) {
        this->mGameSnapshot = snapshot;
    }

    void CRenderer::sleep( long ms ) {
        SDL_Delay(33);
    }

    void CRenderer::handleSystemEvents() {
        SDL_Event event;

        while ( SDL_PollEvent( &event ) ) {

            if( event.type == SDL_QUIT ) {
#ifndef __EMSCRIPTEN__
                exit(0);
#endif
            }

            if ( event.type == SDL_KEYUP ) {
                switch ( event.key.keysym.sym ) {
		case SDLK_q:
#ifndef __EMSCRIPTEN__
		  exit(0);
#endif
		case SDLK_LEFT:
                        mOnKeyReleasedCallback( ECommand::kLeft );
                        break;
		default:
		  break;
                }
            }

            if ( event.type == SDL_KEYDOWN ) {
                switch ( event.key.keysym.sym ) {
		case SDLK_LEFT:
		  mOnKeyPressedCallback( ECommand::kLeft );
		  break;
		default:
		  break;
                }
            }

        }
    }

    void CRenderer::render( long ms ) {
        SDL_Rect rect;
	std::vector<std::tuple< int, int, int >> toDraw;
        rect = { 0, 0, 640, 480 };
        SDL_FillRect( video, &rect, SDL_MapRGB( video->format, 0, 0, 0 ) );

        int y = 0;
        int x = 0;
	int val = 0;
        for ( auto line : mGameSnapshot.state ) {
            x = 0;
            ++y;
            for ( auto item : line ) {
                ++x;
		toDraw.emplace_back( x, y, item );
	    }
	}

	for ( auto pair : mGameSnapshot.visited ) {
	  toDraw.emplace_back( pair.first, pair.second, 3 );
	}

	for ( auto tuple : toDraw ) {
	
	  x = std::get<0>(tuple);
	  y = std::get<1>(tuple);
	  val = std::get<2>(tuple);

	  rect = { (Sint16)(x * 20), (Sint16)(y * 20), 20, 20 };
	  
	  if ( val == 1 ) {
	    SDL_FillRect( video, &rect, SDL_MapRGB( video->format, 128, 128, 128 ) );
	  } else if ( val == 0 ) {
	    SDL_FillRect( video, &rect, SDL_MapRGB( video->format, 0, 128, 0 ) );
	  } else if ( val == 2 ) {
	    SDL_FillRect( video, &rect, SDL_MapRGB( video->format, 255, 0, 0 ) );
	  } else if ( val == 3 ) {
	    SDL_FillRect( video, &rect, SDL_MapRGB( video->format, 0, 0, 255 ) );
	  }
	}
        

        SDL_Flip(video);
    }
}
