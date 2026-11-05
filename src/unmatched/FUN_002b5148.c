extern int DAT_004bf280[4];
int *FUN_002b5148(void) {
    int *p = (int *)((char *)&DAT_004bf280[0] + 0);
    int v = *p;
    int w = v - 1;
    if (v > 0) *p = w;
    return p;
}
