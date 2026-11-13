/* Stores a byte into +82 of an object while the library is active (not mode 1 with no entries). */
struct Object27a {
    char pad0[82];
    signed char flag82;   /* +82 */
};

extern int ps2rna_nvoice;
extern int ps2rna_setup_voice;

void FUN_0027adb8(struct Object27a *object, int value) {
    if (ps2rna_setup_voice != 1 || ps2rna_nvoice > 0) {
        object->flag82 = value;
    }
}
