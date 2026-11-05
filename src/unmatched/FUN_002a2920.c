/* 0x002a2920 — FUN_002a2920 (176 bytes). Updates the clock offset at +3712 from the stream's start time and, for a fresh timing record (f0 == 0), fills it from the clock, video block and stream parameters. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
struct Timing {
    int f0;
    int f4;
    int f8;
    int f12;
    int f16;
    int pad20;
    long f24;
    long f32;
    int f40;
    int f44;
};
struct Timing *FUN_002a2ed0();

struct Params {
    int f0;
    int f4;
    int f8;
    int pad12;
    long f16;
    long f24;                             /* LONG_MAX when unset */
    char pad32[44 - 32];
    int f44;
    int f48;
};
struct Video {
    char pad0[24];
    int f24;                              /* +2340 */
    int f28;                              /* +2344 */
};
struct Clock {
    char pad0[336];
    long f336;                            /* +3704 */
    long f344;                            /* +3712 */
};
struct Player2a2920 {
    char pad0[2316];
    struct Video video;                   /* +2316 */
    char pad2348[3368 - 2316 - (int)sizeof(struct Video)];
    struct Clock clock;                   /* +3368 */
    char pad3720[8052 - 3368 - (int)sizeof(struct Clock)];
    struct Params *params;                /* +8052 */
};

void FUN_002a2920(struct Player2a2920 *player) {
    struct Timing *timing = FUN_002a2ed0(player);
    struct Clock *clock = &player->clock;
    struct Params *params;
    struct Video *video;
    long time;

    if (timing != 0) {
        params = player->params;
        time = params->f24;
        if (time != 0x7FFFFFFFFFFFFFFF) {
            video = &player->video;
            clock->f344 = time - timing->f32;
            if (timing->f0 == 0) {
                timing->f24 = clock->f336;
                timing->f4 = video->f24 * 50;
                timing->f32 = params->f16;
                timing->f8 = video->f28;
                timing->f12 = params->f4;
                timing->f16 = params->f8;
                timing->f40 = params->f44;
                timing->f44 = params->f48;
            }
        }
    }
}
