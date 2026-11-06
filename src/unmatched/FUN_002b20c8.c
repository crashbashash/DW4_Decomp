/* Finds the marker DAT_004f5388 in `text` (FUN_0012aff0) and parses the "major.minor" number that
 * follows it four characters on (FUN_002b2128 twice); returns 1 when found, else 0. */
char *FUN_0012aff0(char *text, char *marker);
char *FUN_002b2128(char *text, int *value);

extern char DAT_004f5388[];

int FUN_002b20c8(char *text, int *major, int *minor) {
    char *found = FUN_0012aff0(text, DAT_004f5388);

    if (found == 0) {
        return 0;
    }
    FUN_002b2128(FUN_002b2128(found + 4, major) + 1, minor);
    return 1;
}
