/* Returns 1 when the first length bytes are all zero, else 0. */
/* Returns 1 when the first `length` bytes are all zero. */
int FUN_002a1730(unsigned char *bytes, int length) {
    int i;

    for (i = 0; i < length; i++) {
        if (*bytes++ != 0) {
            return 0;
        }
    }
    return 1;
}
