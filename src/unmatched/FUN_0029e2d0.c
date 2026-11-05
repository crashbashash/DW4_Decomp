/* 0x0029e2d0 — FUN_0029e2d0 (156 bytes). Under the guard, returns the channel's buffered byte count (+48), or the pending count (+52) plus what its ring holds, saturated to 0x7FFFFFFF. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
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

int FUN_0029e2d0(struct Owner *owner, int index) {
    char guard[16];
    struct ChannelBuf *buf = &owner->channels[index].buf;
    int count;
    int pending;

    FUN_002a0e70(guard);
    count = buf->f32;
    pending = buf->f36;
    if (count == 0 && pending != 0) {
        count = pending + buf->ring->ops->fn36(buf->ring, 1);
    }
    if (count < 0) {
        count = 0x7FFFFFFF;
    }
    FUN_002a0e88(guard);
    return count;
}
