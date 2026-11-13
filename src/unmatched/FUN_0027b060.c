/* PS2RNA_IsOverflow by its message string: not implemented; reports "PS2RNA_IsOverflow: not
 * implemented" (ADXMSG_PrintErr) while the library is active (not mode 1 with no entries) and returns
 * 0. */
extern void ADXMSG_PrintErr(const char *format, ...);
extern int ps2rna_nvoice;
extern int ps2rna_setup_voice;
extern const char PS2RNA_IsOverflow_not_implemented[];

int FUN_0027b060(void) {
    if (ps2rna_setup_voice == 1 && ps2rna_nvoice <= 0) {
        return 0;
    }
    ADXMSG_PrintErr(PS2RNA_IsOverflow_not_implemented);
    return 0;
}
