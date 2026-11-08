/* For a header whose two-digit number (FUN_002b52d8) is at least 2, returns whether the byte at
 * +22 matches DAT_004f5a20 (strncmp over one character); 0 for a null header, a negative
 * index or an older number. */
extern char DAT_004f5a20[];

unsigned int FUN_002b52d8(char *header, int index);
int strncmp(char *a, char *b, int count);

int FUN_002b5490(char *header, int index) {
    if (header == 0 || index < 0) {
        return 0;
    }
    if (FUN_002b52d8(header, index) < 2) {
        return 0;
    }
    return strncmp(header + 22, DAT_004f5a20, 1) != 0;
}
