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
    igMetaField_SetValueFromField(arg0->b, arg0->a, arg2, arg1);
    b = arg0->b;
    sp[0] = 2;
    sp[2] = b;
    sp[1] = (int)arg0;
    igModel_NotifyViews((igModel *)arg0->a, (ModelChange *)sp);
}

void FUN_004551f0(void *arg0v, int arg1, void *arg2v) {
    A_4551f0 *arg0 = (A_4551f0 *)arg0v;
    Rc_4551f0 *arg2 = (Rc_4551f0 *)arg2v;
    Ref_4551f0 sp4C;
    sp4C.p = (Rc_4551f0 *)FUN_00450de0((int)(igObject_GetAllocator((igObject *)arg0v)));
    ObjectList_AppendRetained((igObjectList *)arg0->f8, (igObject *)sp4C.p);
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
    igView_SetModel((igView *)sp4C.p, (igModel *)arg1);
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

int beFontImage_CountTriangles(beFontImage *image, const char *text) {
    int s = 0;
    const char *p = text;
    while (*p != 0) {
        s += ((VC_455370 *)image)->vX(*p);
        p++;
    }
    return s;
}

int beFontImage_CountTrianglesWide(beFontImage *image, const unsigned short *text) {
    int sum;
    const unsigned short *p;
    int c;
    p = text;
    sum = 0;
    while ((c = *p) != 0) {
        sum += ((VC100 *)image)->vX(c);
        p += 1;
    }
    return sum;
}

