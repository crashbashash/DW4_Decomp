/* 0x0029d638 — FUN_0029d638 (188 bytes). Opens channel index: state 4 when its size is 0, otherwise describes datas/sizes[index] via FUN_0029d6f8 (returns its error) and hands that to the channel buffer before entering state 5. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_0029d6f8();
void FUN_0029da68();
void FUN_0029dc18();

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

/* Scratch description filled by FUN_0029d6f8 and consumed by FUN_0029dc18. */
struct Desc29d638 {
    int words[8];
};

int FUN_0029d638(struct Channel *channels, char **datas, int *sizes, int index, int arg4) {
    struct Desc29d638 desc;
    struct Channel *channel = &channels[index];
    struct ChannelBuf *buf = &channel->buf;
    int size;
    int state;
    int flag;
    int status;

    /* matching construct: manual — advancing the two table pointers (not indexing) gives retail's address arithmetic */
    sizes += index;
    datas += index;
    size = *sizes;
    if (size == 0) {
        flag = 0;
        state = 4;
    } else {
        flag = 1;
        state = 5;
        status = FUN_0029d6f8(&desc, *datas, size, arg4);
        if (status != 0) {
            return status;
        }
        FUN_0029dc18(buf, &desc, channel, 1);
    }
    FUN_0029da68(channel, state, flag);
    return 0;
}
