/* 0x0029e9b8 — FUN_0029e9b8 (108 bytes). Sends request 12 with value for channel index through FUN_002b0338 when the channel is closed, then sets the owner flag at +68. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_002b0338();

struct Channel {
    int state;
    int f4;
    char pad8[76 - 8];
    int f76;
    char pad80[116 - 80];
};
struct Owner {
    char pad0[68];
    int f68;
    char pad72[4872 - 72];
    struct Channel channels[1];           /* +4872 */
};

int FUN_0029e9b8(struct Owner *owner, int index, int value) {
    struct Channel *channels = owner->channels;
    struct Channel *channel = &channels[index];
    int result = 0;

    if (channel->f4 == 0) {
        result = FUN_002b0338(owner, channel->f76, 12, value, 0);
    }
    owner->f68 = 1;
    return result;
}
