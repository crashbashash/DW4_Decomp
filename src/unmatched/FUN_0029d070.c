/* 0x0029d070 — FUN_0029d070 (108 bytes). Reports error 0xFF0001A4 when FUN_002a0dd8 refuses the player, otherwise calls ops slot 16 once FUN_002adc40(player, 6) succeeds. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_002a0bb8();
int FUN_002a0dd8();
int FUN_002adc40();

struct Player;
struct PlayerOps {
    char pad[8];
    int (*fn8)(struct Player *, int);
    char pad12[16 - 12];
    int (*fn16)(struct Player *);
};
struct Player {
    char pad[8460];
    struct PlayerOps *ops;
};

int FUN_0029d070(struct Player *player) {
    if (FUN_002a0dd8(player) != 0) {
        FUN_002a0bb8(0, 0xFF0001A4);
        return 0;
    }
    if (FUN_002adc40(player, 6) == 0) {
        return 0;
    }
    return player->ops->fn16(player);
}
