/* Queries FUN_0029dd98 for the player's stream and, on success, returns its start, size and end
 * (f4 + f12) through the out pointers; returns the query status. */
int FUN_0029dd98();

struct Player2a12f8 {
    char pad[8060];
    int f8060;
};
struct Info2a12f8 {
    int f0;
    int f4;
    int f8;
    int f12;
    int rest[4];
};

int FUN_002a12f8(struct Player2a12f8 *player, int *out0, int *out4, int unused, int *outEnd) {
    struct Info2a12f8 info;
    int result;

    result = FUN_0029dd98(player, player->f8060, &info);
    if (result == 0) {
        *out4 = info.f4;
        *out0 = info.f0;
        *outEnd = info.f4 + info.f12;
    }
    return result;
}
