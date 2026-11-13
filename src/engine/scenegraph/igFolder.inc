void Gap__Core__igFolder__vfunc_25(void **arg0) {
    void *temp_a0;

    *arg0 = 0;
    temp_a0 = *arg0;
    if (temp_a0 != 0) {
        *(int *)((char *)(temp_a0) + 4) = (int) (*(int *)((char *)(temp_a0) + 4) + 1);
    }
}

int FUN_001ce400(IniStringObject **out, char *path) {
    IniPathResolver *resolver = DAT_00562788[0];
    if (resolver == 0) {
        *out = 0;
        retain_1ce400(*out);
        return;
    }
    void *allocator = GPR_00554c14 != 0 ? ((void *)Memory_GetAllocatorBySelector(DAT_00587028[0])) : ((void *)Memory_GetAllocatorBySelector(g_temporaryAllocatorSelector[0]));
    igSmartPointer<IniFileObject> file(((IniFileObject *)igFile_Create(allocator)));
    StringObjectRef result(0);
    int opened;
    {
        IniStringRef name = resolver->resolve(path);
        char *text = name.p->text;
        IniFileObject *opener = file.p;
        text = (text == 0) ? DAT_004c22f0[0] : text;
        opened = opener->open(text, DAT_004e47b0);
    }
    if (opened != 0) {
        void *stringAllocator = ((void *)Memory_GetAllocatorBySelector(DAT_00587048[0]));
        release_1ce400(result.p);
        result.p = ((IniStringObject *)FUN_002b9500(stringAllocator));
        FUN_0030b3c0(result.p, file->handle);
        file->close();
    }
    *out = result.p;
    retain_1ce400(*out);
    return 0;
}

int FUN_001ce640(void *arg0, int arg1) {
    return *(int *)(*(int *)((char *)(*(int *)((char *)(arg0) + 116)) + 16) + (arg1 * 4));
}

