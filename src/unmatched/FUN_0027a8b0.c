/* Stores a byte into +80 of an object while the library is active (not mode 1 with no entries). */
struct Object27a {
    char pad0[80];
    signed char flag80;   /* +80 */
};

extern int ps2rna_nvoice;
extern int ps2rna_setup_voice;

void FUN_0027a8b0(struct Object27a *object, int value) {
    if (ps2rna_setup_voice != 1 || ps2rna_nvoice > 0) {
        object->flag80 = value;
    }
}
