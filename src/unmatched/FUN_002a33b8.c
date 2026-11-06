/* Returns FUN_002a8500(player) through *out, or reports error 0xFF000182 when FUN_002a0dd8 refuses
 * the player. */
int FUN_002a0bb8();
int FUN_002a0dd8();
int FUN_002a8500();

int FUN_002a33b8(void *player, int *out) {
    *out = 0;
    if (FUN_002a0dd8(player) != 0) {
        return FUN_002a0bb8(0, 0xFF000182);
    }
    *out = FUN_002a8500(player);
    return 0;
}
