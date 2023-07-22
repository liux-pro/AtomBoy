#include "SDL.h"
#include "stdint.h"

uint8_t sdl_check_key(uint16_t key){
    const Uint8* keystates = SDL_GetKeyboardState(NULL);
    if ( keystates[key] ) {
        return 0;
    } else{
        return 1;
    }
}