int Gap__Sg__igNode__vfunc_26(void **arg0) {
    return ((DW4VC_92_0 *)(arg0))->vX() < 2;
}

void FUN_001c6340(int *arg0, int arg1) {
    unsigned int n;
    unsigned int i;

    if (arg0[7] != 0) {
        n = ((Q_1c6340 *)arg0[7])->count;
    } else {
        n = 0;
    }
    for (i = 0; i < n; i++) {
        ((Q_1c6340 *)arg0[7])->data[i]->vX(arg1);
    }
}

void Gap__Sg__igNode__vfunc_27(void) {

}

void FUN_001c63e0(int arg0, int arg1) {
    int (*temp_v1)(int);

    if (GPR_00554b98 == 0) {
        DAT_00562770[0] = (void *)(((void *)igMetaObject_FindFieldByName(DAT_00585cc8[0], &DAT_004e4640[0])));
        GPR_00554b98 = 1;
    }
    temp_v1 = (int (*)(int))(*(int *)(arg0 + *(int *)((char *)(DAT_00562770[0]) + 8)));
    if (temp_v1 != 0) {
        temp_v1(arg1);
    }
}

void **ObjectRef_Destruct_001c6460(void **arg0, short arg1) {
    int *r;
    if (arg0 != 0) {
        r = (int *)*arg0;
        if (r != 0) {
            r[1] = r[1] - 1;
            if ((r[1] & 0x7fffff) == 0) {
                igObject_Destroy((void *)r);
            }
        }
        if (arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

