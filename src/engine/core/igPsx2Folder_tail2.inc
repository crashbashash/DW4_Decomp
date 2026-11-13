FolderObjectRef Gap__Core__igPsx2Folder__vfunc_26(FolderSelf *self) {
    FolderEntryWide entry;
    int handle = sceDopen(self->path);
    if (handle < 0) {
        return FolderObjectRef(0);
    }
    FolderObjectRef list;
    list.obj = ((FolderObject *)igStringRefList_Create(((int)igObject_GetAllocator((int)self))));
    while (sceDread(handle, &entry) != 0) {
        char *name = (entry.bytes + 64);
        char *interned;
        if (name == 0) {
            interned = 0;
        } else {
            if ((*(int *)g_stringPool) == 0) {
                int v = ((int)StringPool_Allocate(16));
                if (v != 0) {
                    v = ((int)StringPool_Construct((struct S_2eadf0 *)v));
                }
                (*(int *)g_stringPool) = v;
            }
            interned = ((char *)StringPool_Intern((StringPool *)((*(int *)g_stringPool)), (const char *)name));
        }
        FolderStringRef text(interned);
        StringList_AppendRetained(list.obj, &text);
    }
    sceDclose(handle);
    return list;
}

void FUN_0032cac0(struct S_32cac0 *arg0) {
    int i;
    char *s;
    int c;

    s = arg0->f8;
    if (s == 0) {
        s = g_stringObjEmptyText[0];
    }
    i = strlen(s) - 1;
    while ((c = s[i]) == 0x20 || c == 9) {
        i--;
    }
    if (c != 0x5C) {
        if (c != 0x2F) {
            i += 1;
        }
    }
    s[i] = 0;
}

static inline FolderAllocator *currentAllocator(void) {
    if (g_useOwnerAllocator != 0) {
        return ((FolderAllocator *)Memory_GetAllocatorBySelector(g_memoryContextCurrent));
    }
    return ((FolderAllocator *)Memory_GetAllocatorBySelector(g_memoryContextTemporary));
}

int igPsx2_LoadIopModule(int a, int b, int c, int d, int e) {
    int sp1C;
    return FUN_0032cf70((int *)a, b, c, d, e, &sp1C);
}

int FUN_0032cf70(int *arg0, int arg1, int arg2, int arg3, int arg4, int *arg5) {
    int var_v0;
    char *temp_v0;

    if (arg3 > 0xFB) {
        *arg0 = g_resultFailure.v;
        return;
    }
    temp_v0 = FUN_0032cb50((char *)arg1, arg2);
    if (temp_v0 == 0) {
        *arg0 = g_resultFailure.v;
        return;
    }
    if (*temp_v0 == 0x63) {
        do {
            var_v0 = sceSifLoadModule(temp_v0, arg3, arg4);
        } while (var_v0 < 0);
    } else {
        var_v0 = sceSifLoadModule(temp_v0, arg3, arg4);
    }
    if (var_v0 < 0) {
        Memory_FreeBufferAliasA(temp_v0);
        *arg0 = g_resultFailure.v;
        return;
    }
    *arg5 = var_v0;
    Memory_FreeBufferAliasA(temp_v0);
    *arg0 = g_resultSuccess.v;
}

void FUN_0032d070(void)
{
}

void FUN_0032d080(void) {
    int n;
    int v;
    sceDmaReset(1);
    if (DAT_00587340[0] != 0) {
        sceSifInitRpc(0);
        if (DAT_00587338[0] != 0) {
            sceCdInit(0);
        }
        if (DAT_00587348[0] != 0) {
            while (sceSifLoadModule(DAT_00587348[0], 0, 0) < 0) {
            }
        }
        while (((sceSifRebootIop(DAT_00587340[0]) != 0) ^ 1)) {
        }
        while (((sceSifSyncIop() != 0) ^ 1)) {
        }
        DAT_005549b8 = 1;
    }
    if (DAT_005549b8 != 0) {
        sceSifInitRpc(0);
        if (DAT_00587348[0] != 0) {
            sceSifLoadFileReset();
        }
        sceFsReset();
        v = DAT_00587338[0];
        if (v == 1 || v == 0) {
            sceCdInit(0);
            sceCdMmode(1);
        } else if (v == 2) {
            sceCdInit(0);
            sceCdMmode(2);
        }
        sceSifInitCmd();
        n = DAT_004c2628[0];
        sceSifSetCmdBuffer(((int)FUN_002ee430(n * 12)), n);
    }
}

void FUN_0032d1f0(void) {
    FUN_0032d070();
    FUN_0032d080();
}

static inline int internPool(void) {
    if (g_stringPool[0] == 0) {
        int a = ((int)StringPool_Allocate(0x10));
        if (a != 0) {
            a = ((int)StringPool_Construct((S_2eadf0 *)a));
        }
        g_stringPool[0] = a;
    }
    return g_stringPool[0];
}

static inline void setName(O_32d220 *object, int name) {
    int *interned = (int *)((void *)StringPool_Intern((StringPool *)(internPool()), (const char *)name));
    if (object->f72 != 0) {
        int *header = (int *)object->f72 - 2;
        int count = ((int *)object->f72)[-1] - 1;
        ((int *)object->f72)[-1] = count;
        if (count == 0) {
            StringChunk_ReleaseHeader((StringChunkOwnerView *)(*header), (int)header);
        }
    }
    object->f72 = interned;
}

static inline int fileAllocator(void) {
    int a = ((int)FUN_002f8a20());
    return g_useOwnerAllocator != 0 ? a : ((int)Memory_GetAllocatorBySelector(g_memoryContextSystem));
}

void FUN_0032d4b0(int *arg0, char *arg1) {
    int temp_s1;
    int var_v1;
    char *var_a0;

    if ((arg1 != 0) && (strncasecmp(arg1, &text_atfile[0], 7) == 0)) {
        var_a0 = arg1 + 7;
        do {
            var_a0 += 1;
        } while (*var_a0 != 0x2C);
        temp_s1 = (var_a0 - arg1) + 1;
        DAT_00587358[0] = ((int)FUN_002ee430(temp_s1 + 1));
        strncpy(DAT_00587358[0], arg1, temp_s1);
        *(char *)(DAT_00587358[0] + temp_s1) = 0;
        DAT_00587330[0] = DAT_00587358[0];
        FUN_0032ded0(DAT_00587358[0]);
        *arg0 = g_resultSuccess.v;
    } else {
        *arg0 = g_resultFailure.v;
    }
}

