/* Runs FUN_002a4888 for the player and, unless it fails (-1), FUN_002a4a60(player, arg); returns 0
 * or -1. */
int FUN_002a4888();
void FUN_002a4a60();

int FUN_002a4838(void *player, int arg) {
    if (FUN_002a4888(player) == -1) {
        return -1;
    }
    FUN_002a4a60(player, arg);
    return 0;
}
