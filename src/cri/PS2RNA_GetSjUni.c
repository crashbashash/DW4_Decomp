/* Returns the word at +8 of the channel object for one channel of a voice (channel table at +8,
 * one pointer per channel) while the library is active (not mode 1 with no entries); returns 0
 * otherwise. */
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

extern int ps2rna_nvoice;
extern int ps2rna_setup_voice;

int PS2RNA_GetSjUni(struct Voice27b *voice, int channel) {
    if (ps2rna_setup_voice == 1 && ps2rna_nvoice <= 0) {
        return 0;
    }
    return voice->channels[channel]->value8;
}
