/* Scans forward while at least 4 bytes remain and returns the first position where MPS_GetStartCodeKind
 * yields wanted, or 0. */
int MPS_GetStartCodeKind();

char *FUN_0029f798(char *p, int remaining, int wanted) {
    while (remaining >= 4) {
        if (MPS_GetStartCodeKind(p) == wanted) {
            return p;
        }
        remaining--;
        p++;
    }
    return 0;
}
