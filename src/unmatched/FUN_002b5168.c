/* Builds a fixed-layout header in `out`: an 8-character tag (DAT_004f59f8), the number 19
 * formatted with DAT_004f5a08 appended, then at +16 a 2-character field (DAT_004f5a10), the value
 * written by FUN_002b51f8 and the suffix DAT_004f5a18. */
extern char DAT_004f59f8[];
extern char DAT_004f5a08[];
extern char DAT_004f5a10[];
extern char DAT_004f5a18[];

char *strncpy(char *dst, const char *src, unsigned int count);
int sprintf(char *dst, const char *format, ...);
char *FUN_0012a1e8(char *dst, char *src);
void FUN_002b51f8(char *dst, int value);

void FUN_002b5168(char *out, int unused, int value) {
    char number[16];
    char *field;

    strncpy(out, DAT_004f59f8, 8);
    sprintf(number, DAT_004f5a08, 19);
    field = out + 16;
    FUN_0012a1e8(out, number);
    strncpy(field, DAT_004f5a10, 2);
    FUN_002b51f8(field, value);
    FUN_0012a1e8(field, DAT_004f5a18);
}
