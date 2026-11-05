/* 0x002a4730 — FUN_002a4730 (76 bytes). Copies the first two words of the player's FUN_0029dd98 info into *out, or zeroes them when the query fails. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_0029dd98();

struct Player2a4730 {
    char pad[8128];
    int f8128;
};
struct Info2a4730 {
    int f0;
    int f4;
    int rest[6];
};
struct Pair2a4730 {
    int f0;
    int f4;
};

void FUN_002a4730(struct Player2a4730 *player, struct Pair2a4730 *out) {
    struct Info2a4730 info;

    if (FUN_0029dd98(player, player->f8128, &info) != 0) {
        out->f0 = 0;
        out->f4 = 0;
    } else {
        out->f0 = info.f0;
        out->f4 = info.f4;
    }
}
