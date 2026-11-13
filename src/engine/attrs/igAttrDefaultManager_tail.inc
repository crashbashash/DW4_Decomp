igObjectPointer Gap__Attrs__igAttrDefaultManager__vfunc_23(DefaultSource *source) {
    igObjectPointer created = source->create();
    igObjectPointer wrapped = FUN_0013ba30((int)(FUN_0013c060()), igObjectPointer(created.get(), kRetainReference));
    return wrapped;
}

void **FUN_0013bfe0(void **arg0, short arg1) {
    int *r;
    if (arg0 != 0) {
        r = (int *)*arg0;
        if (r != 0) {
            r[1] = r[1] - 1;
            if ((r[1] & 0x7fffff) == 0) {
                igObject_Destroy(r);
            }
        }
        if (arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

struct Ref *FUN_0013c060(void) {
    int a;
    struct Ref *p;
    if (DAT_0055f4b8[0] == 0) {
        if (g_useOwnerAllocator != 0) { int x = Memory_GetAllocatorBySelector(DAT_00587028[0]); a = x; } else { int y = Memory_GetAllocatorBySelector(DAT_005870f8[0]); a = y; }
        p = DAT_0055f4b8[0];
        if (p != 0) {
            p->u.w = p->u.w - 1;
            if (p->u.b.cnt == 0) igObject_Destroy(p);
        }
        DAT_0055f4b8[0] = (struct Ref *)FUN_0013a640(a);
    }
    return DAT_0055f4b8[0];
}

void FUN_0013c110(void) {
    char *o = (char *)DAT_0055f4b8[0];
    if (o != 0) {
        *(int *)(o + 4) = *(int *)(o + 4) - 1;
        if (((unsigned long long) ((long long) *(int *)(o + 4) << 0x29) >> 0x29) == 0) {
            igObject_Destroy(o);
        }
    }
    DAT_0055f4b8[0] = 0;
}

void FUN_0013c170(void) {

}

