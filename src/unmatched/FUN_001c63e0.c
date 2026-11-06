void *igMetaObject_FindFieldByName();
extern int DAT_004e4640[4];
extern void * DAT_00562770[4];
extern int DAT_00585cc8[4];
extern char GPR_00554b98;

void FUN_001c63e0(int arg0, int arg1) {
    int (*temp_v1)(int);

    if (GPR_00554b98 == 0) {
        DAT_00562770[0] = (void *)(igMetaObject_FindFieldByName(DAT_00585cc8[0], &DAT_004e4640[0]));
        GPR_00554b98 = 1;
    }
    temp_v1 = (int (*)(int))(*(int *)(arg0 + *(int *)((char *)(DAT_00562770[0]) + 8)));
    if (temp_v1 != 0) {
        temp_v1(arg1);
    }
}
