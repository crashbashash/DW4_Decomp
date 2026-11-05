/* 0x002a6308 — FUN_002a6308 (92 bytes). Returns whether picture kind is accepted in the context's mode: kinds 2-3 in mode 2, only kind 3 in mode 3, none otherwise. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
struct Context2a6308 {
    char pad0[116];
    unsigned int mode;                    /* +116 */
};
struct Player2a6308 {
    char pad0[8120];
    struct Context2a6308 *context;        /* +8120 */
};

int FUN_002a6308(struct Player2a6308 *player, int kind) {
    unsigned int mode = player->context->mode;
    int result = 0;

    switch (mode) {
    case 4: /* matching construct: manual — explicit empty case shapes the compare tree */
        break;
    case 2:
        if ((unsigned int)(kind - 2) < 2) {
            result = 1;
        }
        break;
    case 3:
        result = kind == mode;
        break;
    }
    return result;
}
