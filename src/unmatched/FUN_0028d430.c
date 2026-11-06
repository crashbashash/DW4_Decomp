/* Scans size bytes for the start code 00 00 01 <code> and returns its address, or 0. */

unsigned char *FUN_0028d430(unsigned char *p, int size, unsigned char code) {
    int i;

    for (i = 0; i + 3 < size; i++, p++) {
        if (p[0] == 0 && p[1] == 0 && p[2] == 1 && p[3] == code) {
            return p;
        }
    }
    return 0;
}
