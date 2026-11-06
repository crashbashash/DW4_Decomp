/* Copies the current picture record (+3560) over the latest one (+3604) when its f36 is older than
 * the player's f3684. */
/* 44-byte picture record. */
struct Picture {
    int f0, f4, f8, f12, f16, f20, f24, f28, f32;
    int f36;
    int f40;
};
struct Player2a6870 {
    char pad0[3560];
    struct Picture current;               /* +3560 */
    struct Picture latest;                /* +3604 */
    char pad3648[3684 - 3648];
    int f3684;
};

/* Copies the current picture record to the latest one when its f36 is older than the player's f3684. */
void FUN_002a6870(struct Player2a6870 *player) {
    struct Picture *current = &player->current;

    struct Picture *latest = &player->latest;

    if (current->f36 < player->f3684) {
        *latest = *current;
    }
}
