void Gap__Gui__igOnOffValueObserver__vfunc_24(void *arg0, void *arg1) {
    if ((*(int *)((char *)arg1 + 8) == *(int *)0x58C290) || (*(int *)((char *)arg1 + 0) == 0)) {
        FUN_00457ab0((igRadioGroup *)(*(int *)((char *)arg0 + 12)), (igRadioGroupSelectedObserver *)arg0, (int)arg0);
    }
}

void FUN_00457c40(struct S_457c40 *arg0, unsigned char arg1) {
    int sp[3];
    unsigned char temp_a2;
    struct T_457c40 *temp_v1;
    unsigned char *pb;

    temp_v1 = arg0->t;
    if (temp_v1 != 0) {
        temp_a2 = temp_v1->b;
        pb = &temp_v1->b;
        if (temp_a2 != arg1) {
            *pb = arg1;
            sp[0] = 2;
            sp[1] = 0;
            sp[2] = DAT_0058c290[0];
            FUN_004578c0((S_4578c0 *)arg0->t, (S_4578c0 *)sp);
        }
    }
}

void FUN_00457ca0(O_457ca0 *arg0, R_457ca0 *arg1) {
    R_457ca0 *old;
    R_457ca0 *a;

    old = arg0->r;
    if (old != arg1) {
        if (old != 0) {
            arg0->v96();
        }
        if (arg1 != 0) {
            arg1->refs = arg1->refs + 1;
        }
        a = arg0->r;
        if (a != 0) {
            a->refs = a->refs - 1;
            if ((a->refs & 0x7FFFFF) == 0) {
                igObject_Destroy(a);
            }
        }
        arg0->r = arg1;
        if (arg0->r != 0) {
            arg0->v92();
        }
    }
}

