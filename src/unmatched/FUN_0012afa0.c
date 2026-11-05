/* 0x0012afa0 — FUN_0012afa0 (80 bytes). Returns the last occurrence of a character in a string (the terminator included), or 0 (newlib strrchr shape; name is a hypothesis). Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
char *FUN_0012afa0(const char *string, int character) {
    const char *last = 0;
    char wanted = character;

    while (*string) {
        if (*string == wanted) {
            last = string;
        }
        string++;
    }
    if (*string == wanted) {
        last = string;
    }
    return (char *)last;
}
