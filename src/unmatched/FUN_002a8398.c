/* Releases one reference on the player's entry id (count clamped at 0, error 0xFF000F31 when
 * missing) and decrements the player's count at +2428; error 0xFF000189 when refused. */
void FUN_002a0bb8();
int FUN_002a0dd8();
struct Entry2a8398 {
    int f0;
    int count;
};
struct Entry2a8398 *FUN_002a8440();

struct Player2a8398 {
    char pad0[2428];
    int f2428;
};

void FUN_002a8398(struct Player2a8398 *player, int id) {
    struct Entry2a8398 *entry;
    int count;

    if (FUN_002a0dd8(player) != 0) {
        FUN_002a0bb8(0, 0xFF000189);
    } else {
        entry = FUN_002a8440(player, id);
        if (entry == 0) {
            FUN_002a0bb8(player, 0xFF000F31);
        } else {
            count = entry->count - 1;
            entry->count = count < 0 ? 0 : count;
        }
        player->f2428--;
    }
}
