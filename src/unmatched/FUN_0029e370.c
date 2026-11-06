/* Returns the ring of channel index through *out, or reports error 0xFF000401 when the channel is
 * not open. */
int FUN_002a0bb8();

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

int FUN_0029e370(struct Owner *owner, int index, struct Ring **out) {
    struct Channel *channels = owner->channels;
    struct Channel *channel;

    *out = 0;
    channel = &channels[index];
    if (channel->f4 == 0) {
        return FUN_002a0bb8(owner, 0xFF000401);
    }
    *out = channel->buf.ring;
    return 0;
}
