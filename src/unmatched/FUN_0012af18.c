/* 0x0012af18 — FUN_0012af18 (132 bytes). Returns the first character of the string that is one of the accept characters, or 0 (newlib strpbrk shape; name is a hypothesis). Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
char *FUN_0012af18(const char *string, const char *accept) {
    const char *candidate = accept;

    if (!*string) {
        return 0;
    }
    while (*string) {
        for (candidate = accept; *candidate; candidate++) {
            if (*string == *candidate) {
                break;
            }
        }
        if (*candidate) {
            break;
        }
        string++;
    }
    if (*candidate == '\0') {
        string = 0;
    }
    return (char *)string;
}
