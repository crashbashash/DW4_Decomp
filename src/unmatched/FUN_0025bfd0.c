/* 0x0025bfd0 — FUN_0025bfd0 (100 bytes). Recognises an AIFF header: "FORM" at +0 and "AIFF" at +8. FUN_00127004
 * compares like memcmp (pointer, pointer, length). Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_00127004(const void *a, const void *b, unsigned int size);

extern const char s_FORM_004ecfa8[];
extern const char s_AIFF_004ecfb0[];

int FUN_0025bfd0(const char *header) {
    if (FUN_00127004(header, s_FORM_004ecfa8, 4) == 0 && FUN_00127004(header + 8, s_AIFF_004ecfb0, 4) == 0) {
        return 1;
    }
    return 0;
}
