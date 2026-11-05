/* 0x002a4838 — FUN_002a4838 (76 bytes). Runs FUN_002a4888 for the player and, unless it fails (-1), FUN_002a4a60(player, arg); returns 0 or -1. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_002a4888();
void FUN_002a4a60();

int FUN_002a4838(void *player, int arg) {
    if (FUN_002a4888(player) == -1) {
        return -1;
    }
    FUN_002a4a60(player, arg);
    return 0;
}
