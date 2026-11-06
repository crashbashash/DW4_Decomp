/* When FUN_002a8500 reports -1, or 1 with FUN_002a84e0 set and state f24 pending, calls
 * FUN_002a3c18(player, 1) and, if state f0 is clear, FUN_002ada78(player, 5, 0). */
void FUN_002a3c18();
int FUN_002a84e0();
int FUN_002a8500();
void FUN_002ada78();

struct State2a3b70 {
    int f0;                               /* +2384 */
    char pad4[24 - 4];
    int f24;                              /* +2408 */
};
struct Player2a3b70 {
    char pad0[2384];
    struct State2a3b70 state;             /* +2384 */
};

void FUN_002a3b70(struct Player2a3b70 *player) {
    struct State2a3b70 *state = &player->state;
    int status = FUN_002a8500(player);

    if (status == -1 || (FUN_002a84e0(player) != 0 && status == 1 && state->f24 != 0)) {
        FUN_002a3c18(player, 1);
        if (state->f0 == 0) {
            FUN_002ada78(player, 5, 0);
        }
    }
}
