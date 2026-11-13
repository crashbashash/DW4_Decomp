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

igAttrPool *FUN_0013c060(void) {
    int allocator;
    if (g_igAttrPool_instance == 0) {
        if (g_useOwnerAllocator != 0) { int owner = Memory_GetAllocatorBySelector(DAT_00587028[0]); allocator = owner; } else { int fallback = Memory_GetAllocatorBySelector(DAT_005870f8[0]); allocator = fallback; }
        g_igAttrPool_instance.release();
        g_igAttrPool_instance.p = (igAttrPool *)FUN_0013a640(allocator);
    }
    return g_igAttrPool_instance;
}

void FUN_0013c110(void) {
    g_igAttrPool_instance.clear();
}

void FUN_0013c170(void) {

}

