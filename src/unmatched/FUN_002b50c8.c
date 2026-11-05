/* 0x002b50c8 — 12 bytes. Stores arg1 at +4 of the object pointed to by arg0+0x28 and
 * returns that object (v0); the pointer must live in v0, so return it rather than discard. */
int FUN_002b50c8(void *arg0, int arg1) {
    void *p = *(void **)((char *)(arg0) + 40);
    *(int *)((char *)p + 4) = arg1;
    return (int) p;
}
