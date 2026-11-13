/* Updates the byte at +86 of an object to the new value when it differs, only while the library is
 * active (not mode 1 with no entries) and 0x004b1e08 is 2. */
struct Object27a {
    char pad0[86];
    signed char flag86;   /* +86 */
};

extern int ps2rna_nvoice;
extern int ps2rna_setup_voice;
extern int DAT_004b1e08;

void FUN_0027a090(struct Object27a *object, int value) {
    if ((ps2rna_setup_voice != 1 || ps2rna_nvoice > 0) && DAT_004b1e08 == 2 && object->flag86 != value) {
        object->flag86 = value;
    }
}
