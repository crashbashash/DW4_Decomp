/* 0x0029dd10 — FUN_0029dd10 (72 bytes). Copies the 16-byte entry in slot `slot` of channel index out to *out. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
/* A 16-byte entry with byte alignment, so whole-entry copies use ldl/ldr and sdl/sdr. */
struct Entry16 {
    char bytes[16];
};
struct Channel {
    int state;
    int f4, f8, f12;
    struct Entry16 entries[3];            /* +16 */
    char pad64[116 - 64];
};
struct Owner29dd10 {
    char pad[4872];
    struct Channel channels[1];           /* +4872 */
};

void FUN_0029dd10(struct Owner29dd10 *owner, int index, int slot, struct Entry16 *out) {
    struct Channel *channels = owner->channels;
    struct Channel *channel = &channels[index];
    struct Entry16 *entries = channel->entries;

    entries += slot; /* matching construct: manual — advancing the pointer keeps retail's base-first address sum */
    *out = *entries;
}
