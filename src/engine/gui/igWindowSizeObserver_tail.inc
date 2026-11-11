void Gap__Gui__igWindowSizeObserver__vfunc_24(void *arg0, int *arg1) {
    int sp30[3];
    struct T_455b90 *temp_s0;
    if ((arg1[2] == DAT_0058c3d0[0]) || (arg1[0] == 0)) {
        temp_s0 = *(struct T_455b90 **)((char *)arg0 + 8);
        FUN_00191860((char *)temp_s0 + 0x60, 0.0f, temp_s0->w, temp_s0->h, 0.0f, 0.0f, 2.0f);
        sp30[0] = 2;
        sp30[1] = (int)arg0;
        sp30[2] = DAT_0058c3f0[0];
        FUN_004578c0((S_4578c0 *)temp_s0, (S_4578c0 *)sp30);
    }
}

