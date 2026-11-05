/* 0x00281ac0 — FUN_00281ac0 (244 bytes). Queues a 20-byte entry (two halfwords, four words) in the context's 128-slot ring at +164 if the write slot is free and the count is not negative; returns 0 or -1. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */

struct Entry00281ac0 {
    unsigned short kind;  /* +0: 0 = free slot */
    unsigned short arg;   /* +2 */
    int a, b, c, d;       /* +4..+16 */
};

/* Context reached through DAT_004bb114 (only the members used here). */
struct Ctx00281ac0 {
    char pad0[164];
    struct Entry00281ac0 ring[128]; /* +164 */
    signed char count;              /* +2724 */
    unsigned char writeIndex;       /* +2725: wraps at 128 */
};

extern struct Ctx00281ac0 *DAT_004bb114;

int FUN_00281ac0(unsigned short kind, unsigned short arg, int a, int b, int c, int d) {
    struct Ctx00281ac0 *ctx = DAT_004bb114;
    int result = 0;

    if (ctx->count >= 0 && ctx->ring[ctx->writeIndex].kind == 0) {
        ctx->ring[ctx->writeIndex].kind = kind;
        ctx->ring[ctx->writeIndex].arg = arg;
        ctx->ring[ctx->writeIndex].a = a;
        ctx->ring[ctx->writeIndex].b = b;
        ctx->ring[ctx->writeIndex].c = c;
        ctx->ring[ctx->writeIndex].d = d;
        ctx->writeIndex = (ctx->writeIndex + 1) & 0x7F;
        DAT_004bb114->count++;
    } else {
        result = -1;
    }
    return result;
}
