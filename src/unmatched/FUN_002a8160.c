/* 0x002a8160 — FUN_002a8160 (112 bytes). Runs FUN_002a81d0 for the player's context and, on success, sets context f116 = 2 and state 200 when its flag and option 48 are set, else 192. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_002a81d0();
int FUN_002adc40();

struct Context2a8160 {
    char pad0[116];
    int f116;
    int state;                            /* +120 */
};
struct Player2a8160 {
    char pad0[8120];
    struct Context2a8160 *context;        /* +8120 */
};

int FUN_002a8160(struct Player2a8160 *player) {
    struct Context2a8160 *context = player->context;
    int flag[4];
    int ready;
    int status;

    status = FUN_002a81d0(player, context, flag);
    if (status != 0) {
        return status;
    }
    ready = flag[0];
    context->f116 = 2;
    if (ready == 0 || FUN_002adc40(player, 48) == 0) {
        context->state = 192;
    } else {
        context->state = 200;
    }
    return 0;
}
