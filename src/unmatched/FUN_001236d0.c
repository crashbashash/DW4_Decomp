/* 0x001236d0 — FUN_001236d0 (24 bytes). Converts a string through FUN_0012bf90 with no end pointer; the shape of
 * atof over strtod (hypothesis). Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
void FUN_0012bf90(const char *s, char **end);

void FUN_001236d0(const char *s) {
    FUN_0012bf90(s, 0);
}
