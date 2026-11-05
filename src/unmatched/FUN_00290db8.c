/* 0x00290db8 — FUN_00290db8 (136 bytes). Builds the 1024-byte saturation table at 0x4bcce0 (384 zeros, the identity ramp 0..255, 384 x 0xFF) and points DAT_004bccd4 at its middle, so clamp[v] saturates v in -384..639 to 0..255. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern unsigned char DAT_004bcce0[1024];
extern unsigned char *DAT_004bccd4;

void FUN_00290db8(void) {
    unsigned char *p = DAT_004bcce0;
    int i;

    for (i = 0; i < 384; i++) {
        *p++ = 0;
    }
    for (i = 0; i < 256; i++) {
        *p++ = i;
    }
    for (i = 0; i < 384; i++) {
        *p++ = 0xFF;
    }
    DAT_004bccd4 = &DAT_004bcce0[384];
}
