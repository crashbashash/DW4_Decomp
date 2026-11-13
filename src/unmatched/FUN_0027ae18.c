/* Sets the output volume (+56) of a voice, clamped to -999..0, while the library is active (not
 * mode 1 with no entries). */
struct Voice27a {
    char pad0[56];
    int volume;   /* +56 */
};

extern int ps2rna_nvoice;
extern int ps2rna_setup_voice;

void FUN_0027ae18(struct Voice27a *voice, int volume) {
    if (ps2rna_setup_voice != 1 || ps2rna_nvoice > 0) {
        if (volume > 0) {
            volume = 0;
        }
        if (volume < -999) {
            volume = -999;
        }
        voice->volume = volume;
    }
}
