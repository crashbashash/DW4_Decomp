extern int DAT_004fb410[4];
void FUN_00327770(int *arg0, void *arg1, int arg2, long long arg3, char arg4) {
    if (*(unsigned char *)((char *)(arg1) + 140) == 0) {
        *(int *)((char *)(arg1) + 116) = arg2;
        *(long long *)((char *)(arg1) + 120) = arg3;
        *(char *)((char *)(arg1) + 141) = arg4;
        *arg0 = DAT_004fb410[0];
    } else {
        *arg0 = DAT_004fb410[2];
    }
}
