/* Walks 18-byte records until FUN_0026d2e8 reports a hit (sets *found) or length is exhausted;
 * returns the byte offset reached. */
int FUN_0026d2e8();

/* Scans `length` bytes of 18-byte records; stops at the first one FUN_0026d2e8 accepts. */
int FUN_0029bbf8(char *records, int length, int *found) {
    char scratch[16];
    int pos;

    *found = 0;
    for (pos = 0; pos < length; pos += 18) {
        if (FUN_0026d2e8(records, 18, scratch) != 0) {
            *found = 1;
            break;
        }
        records += 18;
    }
    return pos;
}
