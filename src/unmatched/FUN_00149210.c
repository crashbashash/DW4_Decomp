/* 0x00149210 — 24 bytes. Returns bit `arg1` of the u16 field at +0x44, inverted.
 * The field must be shifted as UNSIGNED (retail `srlv`): `(unsigned short)` promotes to
 * signed int, so the shift needs the `(unsigned int)` cast or MWCC emits `srav`. */
int FUN_00149210(void *arg0, int arg1) {
    return (((unsigned int) * (unsigned short *)((char *)(arg0) + 68) >> arg1) & 1) == 0;
}
