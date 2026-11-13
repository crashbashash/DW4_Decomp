void Gap__Gui__igFieldChangeView__vfunc_24(void *arg0, void *arg1) {
    int temp_a0;

    if ((*(int *)((char *)arg1 + 0) == 0) || (*(int *)((char *)arg0 + 16) == *(int *)((char *)arg1 + 8))) {
        temp_a0 = *(int *)((char *)arg0 + 12);
        if (temp_a0 != 0) {
            FUN_004552e0((int *)temp_a0, (int *)arg0);
        }
    }
}

void FUN_004551a0(struct S_4551a0 *arg0, int arg1, int arg2) {
    int sp[3];
    int b;
    FUN_002fd150(arg0->b, arg0->a, arg2, arg1);
    b = arg0->b;
    sp[0] = 2;
    sp[2] = b;
    sp[1] = (int)arg0;
    igModel_NotifyViews((S_4578c0 *)arg0->a, (S_4578c0 *)sp);
}

void FUN_004551f0(void *arg0v, int arg1, void *arg2v) {
    A_4551f0 *arg0 = (A_4551f0 *)arg0v;
    Rc_4551f0 *arg2 = (Rc_4551f0 *)arg2v;
    Ref_4551f0 sp4C;
    sp4C.p = (Rc_4551f0 *)FUN_00450de0(igObject_GetAllocator());
    ObjectList_AppendRetained(arg0->f8, sp4C.p);
    sp4C.p->f12 = (int)arg0;
    Rc_4551f0 *t = sp4C.p;
    if (arg2 != 0) {
        arg2->rc = arg2->rc + 1;
    }
    Rc_4551f0 *old = (Rc_4551f0 *)t->f16;
    if (old != 0) {
        old->rc = old->rc - 1;
        if (((unsigned long long)((long long)old->rc << 0x29) >> 0x29) == 0) {
            igObject_Destroy(old);
        }
    }
    t->f16 = (int)arg2;
    FUN_00457e90((S0_457e90 *)sp4C.p, arg1);
}

void FUN_004552e0(int *arg0, int *arg1) {
    int n = *(int *)(arg0[2] + 8);
    int i = 0;
    while (i < n) {
        int a = ((int *)*(int *)(arg0[2] + 16))[i];
        if (a != (int)arg1) {
            FUN_004551a0((S_4551a0 *)a, arg1[2], arg1[4]);
        }
        i++;
    }
}

int beFontImage_CountTriangles(VC_455370 *arg0, char *arg1) {
    int s = 0;
    char *p = arg1;
    while (*p != 0) {
        s += arg0->vX(*p);
        p++;
    }
    return s;
}

int beFontImage_CountTrianglesWide(void **arg0, unsigned short *arg1) {
    int sum;
    unsigned short *p;
    int c;
    p = arg1;
    sum = 0;
    while ((c = *p) != 0) {
        sum += ((VC100 *)arg0)->vX(c);
        p += 1;
    }
    return sum;
}

