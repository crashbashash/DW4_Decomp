/* 0x0027aed8 — FUN_0027aed8 (80 bytes). PS2RNA_SetBitPerSmpl by its message string: only 16 bits per sample
   is supported, any other value is reported as "PS2RNA_SetBitPerSmpl: not support %d bps" (FUN_002659a0)
   while the library is active (not mode 1 with no entries). Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern void FUN_002659a0(const char *format, ...);
extern int DAT_004b1dc0;
extern int DAT_004b1dc8;
extern const char PS2RNA_SetBitPerSmpl_not_support_d_bps[];

/* matching construct: hand search — int return type with no return value (implicit-int style); a void
   return type lets GCC turn the report call into a sibling call */
int FUN_0027aed8(void *rna, int bits_per_sample) {
    if ((DAT_004b1dc8 != 1 || DAT_004b1dc0 > 0) && bits_per_sample != 16) {
        FUN_002659a0(PS2RNA_SetBitPerSmpl_not_support_d_bps, bits_per_sample);
    }
}
