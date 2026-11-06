/* Returns the last occurrence of a character in a string (the terminator included), or 0 (newlib
 * strrchr shape; name is a hypothesis). */
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
