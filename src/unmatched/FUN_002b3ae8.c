int FUN_002b3030();
int FUN_002b4330();
extern int DAT_004bec28[4];
void FUN_002b3ae8(void *arg0) {
    int temp_s0;

    if (arg0 != 0) {
        temp_s0 = *(int *)((char *)(arg0) + 52);
        *(int *)((char *)(arg0) + 0) = 0;
        FUN_002b4330(*(int *)((char *)(arg0) + 40));
        FUN_002b3030(temp_s0);
        DAT_004bec28[0] -= 1;
    }
}
