/* Stores a byte into +91 of an object while the library is active (not mode 1 with no entries). */
struct Object27a {
    char pad0[91];
    signed char flag91;   /* +91 */
};

extern int ps2rna_nvoice;
extern int ps2rna_setup_voice;

void PS2RNA_SetStopFlag(struct Object27a *object, int value) {
    if (ps2rna_setup_voice != 1 || ps2rna_nvoice > 0) {
        object->flag91 = value;
    }
}
