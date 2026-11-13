/* PS2RNA_SetBitPerSmpl by its message string: only 16 bits per sample is supported, any other
 * value is reported as "PS2RNA_SetBitPerSmpl: not support %d bps" (ADXMSG_PrintErr) while the library
 * is active (not mode 1 with no entries). */
extern void ADXMSG_PrintErr(const char *format, ...);
extern int ps2rna_nvoice;
extern int ps2rna_setup_voice;
extern const char PS2RNA_SetBitPerSmpl_not_support_d_bps[];

/* matching construct: hand search — int return type with no return value (implicit-int style); a void
   return type lets GCC turn the report call into a sibling call */
int FUN_0027aed8(void *rna, int bits_per_sample) {
    if ((ps2rna_setup_voice != 1 || ps2rna_nvoice > 0) && bits_per_sample != 16) {
        ADXMSG_PrintErr(PS2RNA_SetBitPerSmpl_not_support_d_bps, bits_per_sample);
    }
}
