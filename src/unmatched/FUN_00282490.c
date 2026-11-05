/* 0x00282490 — FUN_00282490 (164 bytes). Queues a byte-swapped message word for one channel through FUN_00281ac0; requires channel < 32 and a status byte (bit 7), and refuses re-entry. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_00281ac0(unsigned short kind, unsigned short arg, int a, int b, int c, int d);

/* Context reached through DAT_004bb114 (only the members used here). */
struct Ctx002823f0 {
    char pad0[2727];
    signed char sending; /* +2727: -1 while a message is being queued */
};

extern struct Ctx002823f0 *DAT_004bb114;

/* Byte-reversed 32-bit message word, as queued for the IOP. */
#define SWAP32(x) (((x) << 24) | (((x) & 0xFF00) << 8) | (((x) >> 8) & 0xFF00) | ((x) >> 24))

int FUN_00282490(unsigned int channel, unsigned int message) {
    struct Ctx002823f0 *ctx = DAT_004bb114;
    int result;

    if (ctx->sending != 0) {
        return -3;
    }
    if (channel >= 32) {
        return -128;
    }
    ctx->sending = -1;
    if (!(message & 0x80)) {
        DAT_004bb114->sending = 0;
        return -2;
    }
    result = FUN_00281ac0(1, channel, 0, 0, SWAP32(message), 0);
    DAT_004bb114->sending = 0;
    return result;
}
