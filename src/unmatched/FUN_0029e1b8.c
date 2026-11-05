/* 0x0029e1b8 — FUN_0029e1b8 (112 bytes). Reads the position pair at +40 of channel index under the FUN_002a0e70/FUN_002a0e88 guard. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
void FUN_002a0e70();
void FUN_002a0e88();

struct Ring;
struct RingOps {
    char pad[36];
    int (*fn36)(struct Ring *, int);      /* bytes available on a side */
};
struct Ring {
    struct RingOps *ops;
};
/* Read/write position pair at +40 in a channel. */
struct ChannelPos {
    int f0;                               /* +40 */
    int f4;                               /* +44 */
};
struct ChannelBuf {
    char *data;                           /* +16 */
    struct Ring *ring;                    /* +20 */
    int f8, f12, f16, f20;
    struct ChannelPos pos;                /* +40 */
    int f32;                              /* +48 */
    int f36;                              /* +52 */
    int f40, f44;
};
struct Channel {
    int state;
    int f4;
    int f8, f12;
    struct ChannelBuf buf;                /* +16 */
    char pad64[116 - 64];
};
struct Owner {
    char pad[4872];
    struct Channel channels[1];           /* +4872 */
};

void FUN_0029e1b8(struct Owner *owner, int index, int *out0, int *out4) {
    char guard[16];
    struct ChannelPos *pos = &owner->channels[index].buf.pos;

    FUN_002a0e70(guard);
    *out0 = pos->f0;
    *out4 = pos->f4;
    FUN_002a0e88(guard);
}
