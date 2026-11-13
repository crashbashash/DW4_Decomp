/* Sends request 11 with a one-word payload through DTX_CallUrpc, unless the library is in mode 1
 * (0x004b1dc8) with no entries (0x004b1dc0). */
extern void DTX_CallUrpc(int request, int *payload, int words, int a3, int t0);
extern int ps2rna_nvoice;
extern int ps2rna_setup_voice;

void FUN_00279dd0(int value) {
    int payload;

    if (ps2rna_setup_voice != 1 || ps2rna_nvoice > 0) {
        payload = value;
        DTX_CallUrpc(11, &payload, 1, 0, 0);
    }
}
