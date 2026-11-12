int Gap__Sg__igLightSet__vfunc_30(void) {
    return 1;
}

void Gap__Sg__igLightSet__vfunc_09(void **arg0, int arg1) {
    Gap__Sg__igNode__vfunc_09(arg0, arg1);
    if (arg1 == 0) {
        ((DW4VC_112_2 *)(arg0))->vX((int)(1), (int)(1));
    }
}

void Gap__Sg__igLightSet__vfunc_31(O_1d0330 *arg0) {
    unsigned int n;
    unsigned int i;
    n = arg0->l->n;
    for (i = 0; i < n; i++) {
        arg0->l->a[i]->vX();
    }
}

void Gap__Sg__igLightSet__vfunc_27(S_1d03b0 *arg0, int arg1) {
    int sp70[4];
    int sp60[4];
    unsigned int n;
    unsigned int i;
    LS *o;

    n = arg0->list->n;
    for (i = 0; i < n; i++) {
        o = (LS *)arg0->list->data[i];
        FUN_00192fc0(sp70, (char *)o + ((D_1d03b0 * *)DAT_0055f0a0)[0]->off, arg1);
        o->vA(sp70);
        FUN_00192f50(sp60, (char *)o + ((D_1d03b0 * *)DAT_0055f0c0)[0]->off, arg1);
        o->vB(sp60);
    }
}

void thunk_Gap__Sg__igNode__vfunc_09(void **self, int flag) {
    Gap__Sg__igNode__vfunc_09((void * *)self, flag);
}

