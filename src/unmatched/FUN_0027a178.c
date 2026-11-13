/* Unless mode ps2rna_setup_voice is 1 with no pending count in ps2rna_nvoice, closes channel id (0 or 1):
 * when its slot in DAT_004b1e00 is set, sends command 17 with the id through DTX_CallUrpc and
 * clears the slot. */
extern int ps2rna_setup_voice;
extern int ps2rna_nvoice;
extern int DAT_004b1e00[2];
int DTX_CallUrpc(int command, unsigned int *args, int count, int a3, int t0);

void FUN_0027a178(unsigned int id) {
    unsigned int args[4];

    if (ps2rna_setup_voice == 1 && ps2rna_nvoice <= 0) {
        return;
    }
    if (id < 2 && DAT_004b1e00[id] != 0) {
        args[0] = id;
        DTX_CallUrpc(17, args, 1, 0, 0);
        DAT_004b1e00[id] = 0;
    }
}

