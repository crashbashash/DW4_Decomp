/* Queues kind-3 command 0x1000 for slot id 1..24 (see FUN_00282c20) through FUN_00281ac0, refusing
 * re-entry. */
int FUN_00281ac0(unsigned short kind, unsigned short arg, int a, int b, int c, int d);

/* Context reached through DAT_004bb114 (only the members used here). */
struct Ctx002823f0 {
    char pad0[2727];
    signed char sending; /* +2727: -1 while a message is being queued */
};

extern struct Ctx002823f0 *DAT_004bb114;

int FUN_00282d10(int id) {
    struct Ctx002823f0 *ctx = DAT_004bb114;
    int result;

    if (ctx->sending != 0) {
        return -30;
    }
    ctx->sending = -1;
    if ((unsigned int)(id - 1) < 24) {
        result = FUN_00281ac0(3, 0xFFFF, 0x1000, id, 0, 0);
    } else {
        result = -2;
    }
    DAT_004bb114->sending = 0;
    return result;
}
