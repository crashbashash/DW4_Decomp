/* 0x00109368 — 12 bytes. Copies the word at +0x0c into +0x08 and returns it. Declaring
 * it `int` (returning the assigned value) makes MWCC load into v0 as retail does; a void
 * spelling loads into v1 and misses. */
int FUN_00109368(void *arg0) {
    return *(int *)((char *)(arg0) + 12) = *(int *)((char *)(arg0) + 8);
}
