/* Lays eight consecutive areas out from base: areas[i] = base + sizes[0] + ... + sizes[i-1]. The
 * pointer/int split keeps sizes[i] read before the areas[i] store. */
void FUN_0029d5f8(char **areas, int *sizes, char *base) {
    int i;

    for (i = 0; i < 8; i++) {
        areas[i] = base;
        base += sizes[i];
    }
}
