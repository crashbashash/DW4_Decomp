/* 0x0027b1d0 — FUN_0027b1d0 (60 bytes). Returns the word at +8 of the channel object for one channel of a
   voice (channel table at +8, one pointer per channel) while the library is active (not mode 1 with no
   entries); returns 0 otherwise. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
struct Channel27b {
    int f0;
    int value4;    /* +4 */
    int value8;    /* +8 */
};

struct Voice27b {
    int f0;
    int f4;
    struct Channel27b *channels[8];   /* +8 */
};

extern int DAT_004b1dc0;
extern int DAT_004b1dc8;

int FUN_0027b1d0(struct Voice27b *voice, int channel) {
    if (DAT_004b1dc8 == 1 && DAT_004b1dc0 <= 0) {
        return 0;
    }
    return voice->channels[channel]->value8;
}
