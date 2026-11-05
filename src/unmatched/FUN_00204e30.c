extern int DAT_0056bae0[4];
extern int DAT_0056bee0[4];
extern int DAT_0056bee8[4];
extern long long DAT_0056bef0[4];
extern long long DAT_0056bef8[4];
extern long long DAT_0056bf00[4];
extern long long DAT_0056bf08[4];
extern int DAT_0056bf28[4];
void FUN_00204e30(void) {
    int i;

    i = 0;
    do {
        *(int *)((char *)&DAT_0056bae0[0] + (i * 4)) = 0;
        i += 1;
    } while (i < 0x100);
    DAT_0056bee0[0] = 0;
    DAT_0056bf28[0] = 0;
    DAT_0056bee8[0] = 0;
    DAT_0056bef0[0] = 0;
    DAT_0056bef8[0] = 0;
    DAT_0056bf00[0] = 0;
    DAT_0056bf08[0] = 0;
}
