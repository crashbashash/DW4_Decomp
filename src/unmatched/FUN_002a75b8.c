/* Folds the current channel entry's FUN_0029eaf8 value into the player's 64-bit accumulator at
 * +2456 (FUN_0029ecb0). */
void FUN_0029e370();
void FUN_0029eaf8();
long FUN_0029ecb0();

struct Player2a75b8 {
    char pad0[2456];
    long f2456;                           /* 64-bit accumulator */
    char pad2464[8128 - 2464];
    int f8128;
};

void FUN_002a75b8(struct Player2a75b8 *player) {
    int entry;
    int a;
    int b;

    FUN_0029e370(player, player->f8128, &entry);
    if (entry != 0) {
        FUN_0029eaf8(entry, &a, &b);
        player->f2456 = FUN_0029ecb0(player->f2456, a);
    }
}
