/* 0x0029d8f0 — FUN_0029d8f0 (160 bytes). Sets channel index to state 2 (FUN_0029da68) and loads its buffer block with datas[index]/sizes[index], clearing the remaining words. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
void FUN_0029da68();

/* One 116-byte (0x74) channel record; the block at +16 is cleared by FUN_0029d8f0. */
struct ChannelBuf {
    char *data;                           /* +16 */
    int size;                             /* +20 */
    int f8, f12, f16, f20, f24, f28, f32, f36, f40, f44;
};
struct Channel {
    int state;
    int f4, f8, f12;
    struct ChannelBuf buf;                /* +16 */
    char pad64[116 - 64];
};

void FUN_0029d8f0(struct Channel *channels, char **datas, int *sizes, int index) {
    char **data = &datas[index];
    int *size = &sizes[index];
    struct Channel *channel = &channels[index];
    struct ChannelBuf *buf = &channel->buf;

    FUN_0029da68(channel, 2, *size != 0);
    buf->data = *data;
    buf->size = *size;
    buf->f8 = 0;
    buf->f12 = 0;
    buf->f16 = 0;
    buf->f20 = 0;
    buf->f24 = 0;
    buf->f28 = 0;
    buf->f32 = 0;
    buf->f36 = 0;
    buf->f40 = 0;
    buf->f44 = 0;
}
