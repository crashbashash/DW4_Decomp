/* 0x002a4888 — FUN_002a4888 (208 bytes). Advances the player by one decoded step: counts it (FUN_0029edf8, context f136), refreshes the clock and resets the two clock trackers, leaving the context in state 192; -1 on decode error. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
void FUN_0029edf8();
int FUN_002a4958();
int FUN_002a49b8();
int FUN_002a96e0();
int FUN_002aa040();
int FUN_002adc40();
void FUN_002ae248();

struct Clock2a4888 {
    char pad0[60];
    char f60[104 - 60];                   /* reset by FUN_002ae248 */
    char f104[352 - 104];                 /* reset by FUN_002ae248 */
    int f352;
};
struct Context2a4888 {
    char pad0[120];
    int state;                            /* +120 */
    char pad124[136 - 124];
    int f136;                             /* frames counted */
};
struct Player2a4888 {
    char pad0[3368];
    struct Clock2a4888 clock;             /* +3368 */
    char pad3724[8120 - 3368 - (int)sizeof(struct Clock2a4888)];
    struct Context2a4888 *context;        /* +8120 */
};

int FUN_002a4888(struct Player2a4888 *player) {
    struct Clock2a4888 *clock = &player->clock;
    struct Context2a4888 *context = player->context;
    int count;

    if (FUN_002adc40(player, 6) == 0) {
        count = FUN_002a4958(player);
    } else {
        count = FUN_002a49b8(player);
        if (count < 0) {
            return -1;
        }
    }
    if (count > 0) {
        FUN_0029edf8(player, count);
        context->f136++;
        if (FUN_002a96e0(player) != 0) {
            clock->f352 = FUN_002aa040(player) + 1;
        }
    }
    FUN_002ae248(clock->f60, 0x7FFFFFFF);
    FUN_002ae248(clock->f104, -1);
    context->state = 192;
    return 0;
}
