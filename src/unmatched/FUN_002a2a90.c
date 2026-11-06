/* Accumulates channel 0's FUN_0029eaf8 value and the two given amounts into the player's 64-bit
 * totals at +2432..+2448. */
void FUN_0029eaf8();
long FUN_0029ecb0();

struct Player2a2a90 {
    char pad0[2432];
    long f2432;
    long f2440;
    long f2448;
    char pad2456[4892 - 2456];
    void *ring;                           /* +4892: channel 0 ring (4872 + 20) */
};

/* Accumulates the ring's current FUN_0029eaf8 value and the two given amounts into the 64-bit totals at +2432..+2448. */
void FUN_002a2a90(struct Player2a2a90 *player, int amount1, int amount2) {
    void *ring = player->ring;
    int a;
    int b;

    if (ring != 0) {
        FUN_0029eaf8(ring, &a, &b);
        player->f2432 = FUN_0029ecb0(player->f2432, a);
        player->f2440 += amount1;
        player->f2448 += amount2;
    }
}
