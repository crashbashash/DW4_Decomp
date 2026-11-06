/* Scans forward while at least 4 bytes remain and returns the first position where FUN_0028d360
 * yields wanted, or 0. */
int FUN_0028d360();

/* Returns the first position p (while at least 4 bytes remain) where FUN_0028d360(p) == wanted, or 0. */
char *FUN_0029f798(char *p, int remaining, int wanted) {
    while (remaining >= 4) {
        if (FUN_0028d360(p) == wanted) {
            return p;
        }
        remaining--;
        p++;
    }
    return 0;
}
