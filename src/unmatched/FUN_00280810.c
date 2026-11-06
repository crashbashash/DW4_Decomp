extern int DAT_0052d6d0[4];
extern int DAT_0052d6f0[4];
void *FUN_00280810(void *arg0) {
    *(int *)((char *)(arg0) + 0) = (int)(&DAT_0052d6f0[0]);
    *(int *)((char *)(arg0) + 0) = (int)(&DAT_0052d6d0[0]);
    *(int *)((char *)(arg0) + 76) = (int)((int) ((char *)arg0 + 0x50));
    return arg0;
}
