/* The pointer must live in v0, so it is returned rather than discarded. */
int FUN_002b50c8(void *arg0, int arg1) {
    void *p = *(void **)((char *)(arg0) + 40);
    *(int *)((char *)p + 4) = arg1;
    return (int) p;
}
