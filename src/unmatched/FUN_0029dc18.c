/* 0x0029dc18 — FUN_0029dc18 (160 bytes). Under a FUN_002a0e70/FUN_002a0e88 guard, records the flag in the channel and resets the channel buffer from a 24-byte source description. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
void FUN_0029dcb8();
void FUN_002a0e70();
void FUN_002a0e88();
void FUN_002ac6d0();

/* 24-byte source description with byte alignment (copied with ldl/ldr, sdl/sdr). */
struct Span24 {
    char bytes[24];
};
struct ChannelBuf {
    struct Span24 source;                 /* +0 */
    char f24[8];                          /* initialised by FUN_0029dcb8 */
    int f32;
    int f36;
    char f40[8];                          /* initialised by FUN_002ac6d0 */
};
struct Channel {
    int state;
    int f4;
};

void FUN_0029dc18(struct ChannelBuf *buf, struct Span24 *source, struct Channel *channel, int flag) {
    char guard[16];

    FUN_002a0e70(guard);
    channel->f4 = flag;
    __builtin_memcpy(&buf->source, source, 24);
    FUN_0029dcb8(buf->f24);
    buf->f32 = 0;
    buf->f36 = 0;
    FUN_002ac6d0(buf->f40);
    FUN_002a0e88(guard);
}
