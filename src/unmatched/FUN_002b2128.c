/* 0x002b2128 — FUN_002b2128 (136 bytes). Parses a run of decimal digits at `text` (stopping at '.', ' ', NUL or any non-digit), stores the value in *value and returns the position after the digits. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
char *FUN_002b2128(char *text, int *value) {
    char c = *text;
    int number = 0;

    while (c != '.' && c != ' ' && c != '\0' && (unsigned int)(c - '0') < 10) {
        text++;
        number = number * 10 + c - '0';
        c = *text;
    }
    *value = number;
    return text;
}
