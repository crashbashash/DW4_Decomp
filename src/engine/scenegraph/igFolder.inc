void Gap__Core__igFolder__vfunc_25(void **arg0) {
    void *temp_a0;

    *arg0 = 0;
    temp_a0 = *arg0;
    if (temp_a0 != 0) {
        *(int *)((char *)(temp_a0) + 4) = (int) (*(int *)((char *)(temp_a0) + 4) + 1);
    }
}

int FUN_001ce400(IniStringObject **out, char *path) {
    IniPathResolver *resolver = (IniPathResolver *)g_igFolder_instance.p;
    if (resolver == 0) {
        *out = 0;
        retain_1ce400(*out);
        return;
    }
    void *allocator = g_useOwnerAllocator != 0 ? ((void *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleCurrent[0])) : ((void *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleTemporary[0]));
    igSmartPointer<IniFileObject> file(((IniFileObject *)igFile_Create(allocator)));
    StringObjectRef result(0);
    int opened;
    {
        IniStringRef name = resolver->resolve(path);
        char *text = name.p->text;
        IniFileObject *opener = file.p;
        text = (text == 0) ? g_stringObjEmptyText[0] : text;
        opened = opener->open(text, DAT_004e47b0);
    }
    if (opened != 0) {
        void *stringAllocator = ((void *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleString[0]));
        release_1ce400(result.p);
        result.p = ((IniStringObject *)igStringObj_Create(stringAllocator));
        igStringObj_Set(result.p, file->handle);
        file->close();
    }
    *out = result.p;
    retain_1ce400(*out);
    return 0;
}

int FUN_001ce640(void *arg0, int arg1) {
    return *(int *)(*(int *)((char *)(*(int *)((char *)(arg0) + 116)) + 16) + (arg1 * 4));
}

