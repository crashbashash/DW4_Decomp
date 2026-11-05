/* 0x0012a8c8 — FUN_0012a8c8 (76 bytes). Lowercases the string in place using the ctype table's upper-case bit and returns it (newlib strlwr shape; name is a hypothesis). Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern const char DAT_004d3d10[]; /* ctype class table; entry c + 1 classifies character c */

#define CTYPE_UPPER 0x01
#define IS_UPPER(c) ((DAT_004d3d10 + 1)[(int)(c)] & CTYPE_UPPER)

char *FUN_0012a8c8(char *string) {
    char *result = string;

    while (*string != '\0') {
        int c = *string;

        if (IS_UPPER(c)) {
            *string = c - 'A' + 'a';
        }
        ++string;
    }
    return result;
}
