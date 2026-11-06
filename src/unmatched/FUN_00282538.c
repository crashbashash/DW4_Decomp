/* Builds a three-byte message (0xA0|kind for kind 8..13, then two 7-bit data bytes) and queues it
 * for one channel through FUN_00281ac0, refusing re-entry. */
int FUN_00281ac0(unsigned short kind, unsigned short arg, int a, int b, int c, int d);

/* Context reached through DAT_004bb114 (only the members used here). */
struct Ctx002823f0 {
    char pad0[2727];
    signed char sending; /* +2727: -1 while a message is being queued */
};

extern struct Ctx002823f0 *DAT_004bb114;

/* Byte-reversed 32-bit message word, as queued for the IOP. */
#define SWAP32(x) (((x) << 24) | ((x) >> 24) | ((((x) >> 8) & 0xFF00) | (((x) & 0xFF00) << 8)))

int FUN_00282538(unsigned int channel, unsigned int kind, unsigned int data1, unsigned int data2) {
    struct Ctx002823f0 *ctx = DAT_004bb114;
    int result;

    if (ctx->sending != 0) {
        return -3;
    }
    if (channel >= 32) {
        return -128;
    }
    if (kind - 8 >= 6) {
        return -2;
    }
    if (data1 >= 128) {
        return -2;
    }
    if (data2 >= 128) {
        return -2;
    }
    ctx->sending = -1;
    result = FUN_00281ac0(1, channel, 0, 0, ((kind | 0xA0) << 24) | (data1 << 16) | (data2 << 8), 0);
    DAT_004bb114->sending = 0;
    return result;
}
