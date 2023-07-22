#include <SDL2/SDL_timer.h>
#include <SDL.h>

void g_timer0_1ms_fps_callback();

Uint32 TimerCallback(Uint32 interval, void *param) {
    g_timer0_1ms_fps_callback();
    return interval; // 返回下一次定时器触发的间隔时间，返回0将停止定时器
}

void fps_init() {
    if (SDL_Init(SDL_INIT_TIMER) < 0) {
        printf("SDL timer init error");
    }

    Uint32 timerInterval = 1; // 1ms
    SDL_TimerID timerID = SDL_AddTimer(timerInterval, TimerCallback, NULL);
    if (!timerID) {
        printf("SDL timer create error");
    }
}