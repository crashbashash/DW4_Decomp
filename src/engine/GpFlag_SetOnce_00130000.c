/* 0x00130000 — 24 bytes. One-shot initialiser guarded by a byte at the head of
 * .sbss (0x00554b00). First verified GP-relative function: gp = 0x0055c870 comes
 * from the ELF's .reginfo, and gp-32112 == 0x00554b00 is that guard. */
extern unsigned char DAT_00554b00;
void GpFlag_SetOnce_00130000(void) { if (!DAT_00554b00) DAT_00554b00 = 1; }
