/* 0x00123710 — FUN_00123710 (28 bytes). Converts a decimal string through FUN_0012c218 with no end pointer; the
 * shape of atoi over strtol (hypothesis). Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_0012c218(const char *s, char **end, int base);

int FUN_00123710(const char *s) {
    return FUN_0012c218(s, 0, 10);
}
