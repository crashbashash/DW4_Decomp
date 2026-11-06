/* Latches an 8-byte event record into DAT_00585680 and the player context (+4472), sets
 * DAT_00585678 and reports event 0xFF000F40. */
void FUN_002a0bb8();
extern int DAT_00585678;
extern char DAT_00585680[8];

struct Context2a99c8 {
    char pad0[4472];
    char f4472[8];
};
struct Player2a99c8 {
    char pad0[8120];
    struct Context2a99c8 *context;        /* +8120 */
};

/* Latches an 8-byte event record into DAT_00585680 and the context, then reports it as 0xFF000F40. */
int FUN_002a99c8(void *unused, void *record, struct Player2a99c8 *player) {
    DAT_00585678 = 1;
    __builtin_memcpy(DAT_00585680, record, 8);
    __builtin_memcpy(player->context->f4472, record, 8);
    FUN_002a0bb8(player, 0xFF000F40);
    return 1;
}
