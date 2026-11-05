/* 0x0012a710 — FUN_0012a710 (124 bytes). Returns the length of the leading run of the string that contains none of the reject characters (newlib strcspn shape; name is a hypothesis). Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
unsigned int FUN_0012a710(const char *string, const char *reject) {
    const char *start = string;
    const char *candidate;

    while (*string) {
        for (candidate = reject; *candidate; candidate++) {
            if (*string == *candidate) {
                break;
            }
        }
        if (*candidate) {
            break;
        }
        string++;
    }
    return string - start;
}
