/* 0x0025c8b8 — FUN_0025c8b8 (88 bytes). Recognises a Sun/NeXT audio header: ".snd" or ".sd" magic at +0.
 * FUN_00127004 compares like memcmp (pointer, pointer, length). Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_00127004(const void *a, const void *b, unsigned int size);

extern const char s__snd_004ecfb8[];
extern const char s__sd_004ecfc0[];

int FUN_0025c8b8(const char *header) {
    if (FUN_00127004(header, s__snd_004ecfb8, 4) == 0 || FUN_00127004(header, s__sd_004ecfc0, 4) == 0) {
        return 1;
    }
    return 0;
}
