#include "SDL.h"

//处理sdl事件,防止卡住.
void sdl_polling(){
    while (1){
        SDL_Event event;
        /* https://wiki.libsdl.org/SDL_PollEvent */
        if (SDL_PollEvent(&event) != 0) {
            switch (event.type) {
                case SDL_QUIT:
                    exit(0);
            }
        } else{
            break;
        }
    }
}
