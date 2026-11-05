/* 0x002a8088 — FUN_002a8088 (204 bytes). Commits entry id as the context's current one: requires the pending slot to be 1 (error 0xFF000F0E) and FUN_002a8440 to agree with context f112 (error 0xFF000F0F), then clears the slot and calls FUN_002a8668. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_002a0bb8();
int *FUN_002a8158();
int FUN_002a8440();
void FUN_002a8668();

struct Context2a8088 {
    char pad0[112];
    int f112;
};
struct Player2a8088 {
    char pad0[8120];
    struct Context2a8088 *context;        /* +8120 */
};

int FUN_002a8088(struct Player2a8088 *player, int id) {
    struct Context2a8088 *context = player->context;
    int *slot = FUN_002a8158();
    int found;
    int current;

    if (*slot != 1) {
        return FUN_002a0bb8(player, 0xFF000F0E);
    }
    found = FUN_002a8440(player, id);
    current = context->f112;
    if (current != found) {
        return FUN_002a0bb8(player, 0xFF000F0F);
    }
    *slot = 0;
    FUN_002a8668(current);
    return 0;
}
