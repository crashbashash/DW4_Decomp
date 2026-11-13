/* Claims the first unused entry (byte 0 clear) among the ps2rna_nvoice 24-byte entries of
 * ps2rna_psj, marking it used; returns it, or 0 when none is free. */
typedef struct Entry_2796b0 {
    signed char used;   /* 0x00 */
    char pad1[23];
} Entry_2796b0;

extern int ps2rna_nvoice;
extern Entry_2796b0 ps2rna_psj[];

Entry_2796b0 *FUN_002796b0(void) {
    Entry_2796b0 *entry = 0;
    int i;

    for (i = 0; i < ps2rna_nvoice; i++) {
        entry = &ps2rna_psj[i];
        if (entry->used == 0) {
            break;
        }
    }
    if (i == ps2rna_nvoice) {
        return 0;
    }
    entry->used = 1;
    return entry;
}

