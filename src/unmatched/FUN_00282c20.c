/* 0x00282c20 — FUN_00282c20 (236 bytes). Queues a kind-3 entry for all channels; for a message byte of 0xAE or above it first claims one of 24 slots and passes its 1-based id. Returns the id (0 when no slot is needed) or an error. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_00281ac0(unsigned short kind, unsigned short arg, int a, int b, int c, int d);

struct Slot00282c20 {
    unsigned char used;
    char pad1[3];
};

/* Context reached through DAT_004bb114 (only the members used here). */
struct Ctx00282c20 {
    char pad0[2727];
    signed char sending;            /* +2727: -1 while a message is being queued */
    char pad2728[2748 - 2728];
    struct Slot00282c20 slots[24];  /* +2748 */
};

extern struct Ctx00282c20 *DAT_004bb114;

int FUN_00282c20(unsigned int message, int arg) {
    struct Ctx00282c20 *ctx = DAT_004bb114;
    int id = -1;
    int result;
    int i;

    if (ctx->sending != 0) {
        return -30;
    }
    ctx->sending = -1;
    if ((message & 0xFF) >= 0xAE) {
        for (i = 0; i < 24; i++) {
            if (DAT_004bb114->slots[i].used == 0) {
                id = i + 1;
                DAT_004bb114->slots[i].used = 1;
                break;
            }
        }
    } else {
        id = 0;
    }
    if (id >= 0) {
        result = FUN_00281ac0(3, 0xFFFF, 0xF00, id, message, arg);
    } else {
        result = -2;
    }
    if (result == 0) {
        result = id;
    }
    DAT_004bb114->sending = 0;
    return result;
}
