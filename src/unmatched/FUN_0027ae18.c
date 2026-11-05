/* 0x0027ae18 — FUN_0027ae18 (64 bytes). Sets the output volume (+56) of a voice, clamped to -999..0, while
   the library is active (not mode 1 with no entries). Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
struct Voice27a {
    char pad0[56];
    int volume;   /* +56 */
};

extern int DAT_004b1dc0;
extern int DAT_004b1dc8;

void FUN_0027ae18(struct Voice27a *voice, int volume) {
    if (DAT_004b1dc8 != 1 || DAT_004b1dc0 > 0) {
        if (volume > 0) {
            volume = 0;
        }
        if (volume < -999) {
            volume = -999;
        }
        voice->volume = volume;
    }
}
