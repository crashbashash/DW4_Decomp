/* Returns 1 when nothing is pending for picture kind 1..3 (word +8/+12/+16 of the block at +2564),
 * and 1 for any other kind. */
struct Pending2a64c0 {
    char pad0[8];
    int f8;                               /* +2572 */
    int f12;                              /* +2576 */
    int f16;                              /* +2580 */
};
struct Player2a64c0 {
    char pad0[2564];
    struct Pending2a64c0 pending;         /* +2564 */
};

/* Returns 1 when nothing is pending for picture kind 1..3 (2 for other kinds). */
int FUN_002a64c0(struct Player2a64c0 *player, unsigned int kind) {
    struct Pending2a64c0 *pending = &player->pending;

    int value;

    switch (kind) {
    case 1:
        value = pending->f8;
        break;
    case 2:
        value = pending->f12;
        break;
    case 3:
        value = pending->f16;
        break;
    default:
        return 1;
    }
    return value == 0;
}
