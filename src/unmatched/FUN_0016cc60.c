int FUN_001ee270();
int List_Resize();
extern int DAT_0048a4f0[4];
void FUN_0016cc60(char *arg0) {
    int idx;
    int *s2;
    int s1;
    int s0;
    idx = *(int *)(arg0 + 964);
    if (idx >= 0) {
        s2 = **(int ***)(*(int *)(*(int *)(arg0 + 960) + 16) + idx * 4);
        s0 = FUN_001ee270(*(int *)((char *)DAT_0048a4f0 + *(int *)(arg0 + 1400) * 4));
        s1 = *(volatile int *)&s2[2];
        if (s1 < s2[3]) {
            s2[2] = s2[2] + 1;
        } else {
            List_Resize(s2, s1 + 1, 4);
        }
        *(int *)(s2[4] + s1 * 4) = s0;
    }
}
