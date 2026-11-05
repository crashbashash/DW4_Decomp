/* 0x002a05e0 — FUN_002a05e0 (120 bytes). Returns the first id in [first, last] for which FUN_002b1ae0 succeeds with a non-zero result, or 0. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_002b1ae0();

/* Returns the first id in [first, last] for which FUN_002b1ae0 succeeds with a non-zero result, or 0. */
int FUN_002a05e0(void *table, int first, int last) {
    int found;
    int id;

    for (id = first; id <= last; id++) {
        if (FUN_002b1ae0(table, (unsigned char)id, &found) != 0 && found != 0) {
            return id;
        }
    }
    return 0;
}
