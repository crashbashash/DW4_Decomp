/* Sets one entry of the per-channel level table (+64, one word per channel), clamped to -15..15,
 * while the library is active (not mode 1 with no entries). */
struct Voice27a {
    char pad0[64];
    int channel_level[8];   /* +64 */
};

extern int DAT_004b1dc0;
extern int DAT_004b1dc8;

void FUN_0027ae58(struct Voice27a *voice, int channel, int level) {
    int clamped;

    if (DAT_004b1dc8 != 1 || DAT_004b1dc0 > 0) {
        clamped = -15;
        if (level >= -15) {
            clamped = level;
        }
        if (clamped >= 16) {
            clamped = 15;
        }
        voice->channel_level[channel] = clamped;
    }
}
