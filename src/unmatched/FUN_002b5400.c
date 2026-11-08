/* For a header whose two-digit number (FUN_002b52d8) is at least 2, classifies the byte at +21: 1
 * unless it matches DAT_004f5a50 (strncmp over one character), then 2 unless it also matches
 * DAT_004f5a58, then 0; 0 for a null header or a negative index. */
extern char DAT_004f5a50[];
extern char DAT_004f5a58[];

unsigned int FUN_002b52d8(char *header, int index);
int strncmp(char *a, char *b, int count);

int FUN_002b5400(char *header, int index) {
    char *field;
    int kind;

    if (header == 0 || index < 0) {
        return 0;
    }
    if (FUN_002b52d8(header, index) < 2) {
        return 0;
    }
    field = header + 21;
    if (strncmp(field, DAT_004f5a50, 1) == 0) {
        kind = 1;
    } else {
        kind = strncmp(field, DAT_004f5a58, 1) != 0 ? 0 : 2;
    }
    return kind;
}
