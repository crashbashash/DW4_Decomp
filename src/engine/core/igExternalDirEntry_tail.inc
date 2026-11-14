void Gap__Core__igExternalDirEntry__vfunc_31(igExternalDirEntryView *arg0, void *arg1) {
    int s2, v, old, r;
    int *hd;
    s2 = ((igIGBFile *)arg1)->_basePath;
    if (g_stringPool[0] == 0) {
        v = ((int)StringPool_Allocate(16));
        if (v != 0) {
            v = ((int)StringPool_Construct((StringPool *)v));
        }
        g_stringPool[0] = v;
    }
    s2 = StringPool_Intern((StringPool *)g_stringPool[0], (const char *)s2);
    old = arg0->_externalFilePath;
    if (old != 0) {
        hd = (int *)(old - 8);
        v = *(int *)(old - 4) - 1;
        *(int *)(old - 4) = v;
        if (v == 0) {
            StringChunk_ReleaseHeader((StringChunk *)(*hd), (int)hd);
        }
    }
    arg0->_externalFilePath = s2;
    arg0->vfunc_43(((igIGBFile *)arg1)->_userLoadFunction);
    if (arg0->_ref == 0 && GPR_00554c00 == 0) {
        r = FUN_00308390(DAT_004f99f0, arg0->_entryName, arg0->_externalFilePath);
        if (r != 1 && r == 2) {
            GPR_00554c00 = 1;
        }
    }
    FUN_002d7da0((igDirectoryView *)arg1, arg0->_index, arg0->_ref);
}

void FUN_002e26b0(igExternalDirEntry *arg0, int arg1) {
    int *temp_a1;
    int temp_v1;
    int var_v0;
    int *temp_a0;
    int *temp_s0;
    if (g_stringPool[0] == 0) {
        var_v0 = ((int)StringPool_Allocate(0x10));
        if (var_v0 != 0) {
            var_v0 = ((int)StringPool_Construct((StringPool *)var_v0));
        }
        g_stringPool[0] = var_v0;
    }
    temp_s0 = (int *)(((void *)StringPool_Intern((StringPool *)g_stringPool[0], (const char *)arg1)));
    temp_a0 = (int *)arg0->_directoryName;
    if (temp_a0 != 0) {
        temp_a1 = temp_a0 - 2;
        temp_v1 = temp_a0[-1] - 1;
        temp_a0[-1] = temp_v1;
        if (temp_v1 == 0) {
            StringChunk_ReleaseHeader((StringChunk *)(*temp_a1), (int)temp_a1);
        }
    }
    arg0->_directoryName = (int)temp_s0;
}

void Gap__Core__igExternalDirEntry__vfunc_23(igDirEntry *arg0, igObject *arg1) {
    igObject *temp_a0;
    if (arg1 != 0) {
        arg1->_refCount = (int)((int) (arg1->_refCount + 1));
    }
    temp_a0 = (igObject *)((void *)(arg0->_ref));
    if (temp_a0 != 0) {
        temp_a0->_refCount = (int)((int) (temp_a0->_refCount - 1));
        if (((unsigned long long) ((long long)(int) temp_a0->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy(temp_a0);
        }
    }
    arg0->_ref = (int)(arg1);
}

int Gap__Core__igExternalDirEntry__vfunc_44(igExternalDirEntryView *arg0, int arg1) {
    igSmartPointer<igIGBFileView> stream(((igIGBFileView *)FUN_002c37e0(((int)igObject_GetAllocator((int)arg0)))));
    char *s1;
    int len;
    int c;
    char *buf;
    stream.get()->_userLoadFunction = arg1;
    stream.get()->ReadFile((char *)arg0->_directoryName);
    if (stream.get()->_count == 0) {
        s1 = (char *)arg0->_directoryName;
        len = strlen(arg0->_externalFilePath);
        len = len + strlen(s1);
        c = strlen(&DAT_004f9a48[0]);
        buf = (char *)igObject_AllocateStorage((int)arg0, c + len + 1);
        strcpy(buf, arg0->_externalFilePath);
        strcat(buf, &DAT_004f9a48[0]);
        strcat(buf, arg0->_directoryName);
        stream.get()->ReadFile(buf);
        FUN_00300f50((int)arg0, (int)buf);
    }
    arg0->vfunc_23(FUN_002d8e70((int)(stream.get()), arg0->_entryName));
    if (arg0->_ref == 0) {
        arg0->vfunc_23(FUN_002d8e70((int)(stream.get()), (int)&text_root[0]));
    }
    return arg0->_ref != 0;
}

void Gap__Core__igExternalDirEntry__vfunc_11(igDirEntry *arg0) {
    Gap__Core__igDirEntry__vfunc_11((int)arg0);
    arg0->_resolveMethod = 2;
    arg0->_refType = 0;
}

void Gap__Core__igExternalDirEntry__vfunc_12(void **arg0) {
    ((igDirEntryView *)(arg0))->vfunc_23((int)(0));
    Gap__Core__igObject__vfunc_10((int)arg0);
}

