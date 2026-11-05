/* 0x0029e960 — FUN_0029e960 (88 bytes). Sends request 11 with value for channel index through FUN_002b0338 when the channel is closed (+4 == 0). Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
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

int FUN_0029e960(struct Owner *owner, int index, int value) {
    struct Channel *channels = owner->channels;
    struct Channel *channel = &channels[index];

    if (channel->f4 == 0) {
        return FUN_002b0338(owner, channel->f76, 11, value, 0);
    }
    return 0;
}
