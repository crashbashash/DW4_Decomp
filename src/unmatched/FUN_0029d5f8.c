/* 0x0029d5f8 — FUN_0029d5f8 (60 bytes). Lays out eight consecutive areas from base using the sizes table. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
/* Lays eight consecutive areas out from base: areas[i] = base + sizes[0] + ... + sizes[i-1].
 * The pointer/int split lets the scheduler read sizes[i] before the areas[i] store, as retail does. */
void FUN_0029d5f8(char **areas, int *sizes, char *base) {
    int i;

    for (i = 0; i < 8; i++) {
        areas[i] = base;
        base += sizes[i];
    }
}
