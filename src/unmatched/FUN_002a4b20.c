/* 0x002a4b20 — FUN_002a4b20 (68 bytes). Forwards amount to FUN_0029e3d0 for the player's stream at +8128 and adds it to the 64-bit total at +2464. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
void FUN_0029e3d0();

struct Player2a4b20 {
    char pad0[2464];
    long f2464;                           /* running total */
    char pad2472[8128 - 2472];
    int f8128;
};

void FUN_002a4b20(struct Player2a4b20 *player, int amount) {
    FUN_0029e3d0(player, player->f8128, amount);
    player->f2464 += amount;
}
