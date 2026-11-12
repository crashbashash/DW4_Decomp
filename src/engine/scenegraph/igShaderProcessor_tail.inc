#undef SET_OUT
#undef DROP

int Gap__Sg__igShaderProcessor__vfunc_22(void) {
    return DAT_005614f8[0];
}

int FUN_001cafc0(struct L_1cafc0 *arg0, IniStrRef name, int arg2) {
    int n = arg0->n;
    int i = arg2;
    int r;
    while (i < n) {
        if ((int)name.p == arg0->items[i]) { r = i; goto done; }
        i++;
    }
    r = -1;
done:
    return r;
}

void FUN_001cb010(void *self, IniValueTarget *target, IniValueList *list) {
    int i;
    IniValueObject *value;
    char *s;
    igSmartPointer<IniValueObject> text(((IniValueObject *)FUN_002b9500(((void *)igObject_GetAllocator(self)))));
    for (i = 0; i < FUN_00303e50(list); i++) {
        value = FUN_00303e60(list, i);
        if (igObject_IsKindOf(value, FUN_001e4e30()) != 0) {
            FUN_0030b720(text.p, value->value.i, DAT_004e4710);
            s = text.p->value.s;
            s = (s == 0) ? DAT_004c22f0[0] : s;
            FUN_002d9740(target, 10, FUN_00303e80(list, i), s);
        } else if (igObject_IsKindOf(value, FUN_001e4fc0()) != 0) {
            FUN_0030b730(text.p, DAT_004e4718, value->value.f);
            s = text.p->value.s;
            s = (s == 0) ? DAT_004c22f0[0] : s;
            FUN_002d9740(target, 11, FUN_00303e80(list, i), s);
        } else if (igObject_IsKindOf(value, FUN_001e5c50()) != 0) {
            FUN_0030b770(text.p, value->value.b, 0);
            s = text.p->value.s;
            s = (s == 0) ? DAT_004c22f0[0] : s;
            FUN_002d9740(target, 12, FUN_00303e80(list, i), s);
        }
    }
}

void FUN_001cb1f0(int arg0, int arg1, int arg2, int arg3, void **arg4, int arg5) {
    SectionRef section = FUN_001cd9f0((IniShaderFactoryView *)arg0, (char *)arg1);
    if (section.get() != 0) {
        ((DW4VC_96_1 *)(arg4))->vX((int)(section.get()));
        FUN_001cb010((void *)arg0, (IniValueTarget *)section.get(), (IniValueList *)arg5);
        FUN_002da990(section.get(), arg2, arg3, 1);
    }
}

void FUN_001cb2d0(int dummy0, int arg1, int arg2, void *arg3) {
    int temp_v0;

    temp_v0 = FUN_00303dc0(arg1, arg2);
    if (temp_v0 != -1) {
        FUN_00304030(arg1, temp_v0);
    }
    FUN_00303cd0(arg1, arg2, *(int *)((char *)(arg3) + 28));
}

void FUN_001ccb20(int **arg0, int *arg1) {
    int *a;
    *arg0 = *(int **)arg1[4];
    a = *arg0;
    if (a != 0) {
        a[-1] = a[-1] + 1;
    }
}

