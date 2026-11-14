igSmartPointer<igObject> Gap__Core__igPsx2Folder__vfunc_26(igPsx2Folder *self) {
    FolderEntryWide entry;
    int handle = sceDopen(self->_folderName);
    if (handle < 0) {
        /* The empty result is built with the retaining constructor: retail stores the 0 into the
         * result and re-reads it for the reference-count test. */
        return igSmartPointer<igObject>(0, kRetainReference);
    }
    igSmartPointer<igObject> list((igObject *)igStringRefList_Create(((int)igObject_GetAllocator((int)self))));
    while (sceDread(handle, &entry) != 0) {
        char *name = (entry.bytes + 64);
        char *interned;
        if (name == 0) {
            interned = 0;
        } else {
            if ((*(int *)g_stringPool) == 0) {
                int v = ((int)StringPool_Allocate(16));
                if (v != 0) {
                    v = ((int)StringPool_Construct((StringPool *)v));
                }
                (*(int *)g_stringPool) = v;
            }
            interned = ((char *)StringPool_Intern((StringPool *)((*(int *)g_stringPool)), (const char *)name));
        }
        igString text(interned);
        StringList_AppendRetained(list.p, &text);
    }
    sceDclose(handle);
    return list;
}

void FUN_0032cac0(igStringObj *arg0) {
    int i;
    char *s;
    int c;

    s = (char *)arg0->_buffer;
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

static inline igMemoryPoolView *currentAllocator(void) {
    if (g_useOwnerAllocator != 0) {
        return ((igMemoryPoolView *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleCurrent));
    }
    return ((igMemoryPoolView *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleTemporary));
}

char *FUN_0032cb50(char *name, int kind) {
    char *joined = 0;
    char *resolved = 0;
    if (kind == 0) {
        joined = (char *)FUN_002ed5a0(name, currentAllocator());
    } else {
        char *dirs[3];
        const char *key;
        igSmartPointer<igObject> path((igObject *)igStringObj_Create((int)currentAllocator()));
        if (kind == 1) {
            key = text_sonyModulePath;
        } else {
            key = text_intrinsicModulePath;
        }
        if (FUN_00306770(*(int *)(g_objectSystem[0] + 56), 2, key, (igStringObj **)&path, (const char *)DAT_004f7910, 0) != 0) {
            FUN_0032cac0((igStringObj *)path.p);
            char *dir = (char *)((igStringObj *)path.p)->_buffer;
            dir = (dir == 0) ? g_stringObjEmptyText[0] : dir;
            igMemoryPoolView *allocator = currentAllocator();
            joined = (char *)allocator->Allocate(strlen(dir) + strlen(name) + 2);
            sprintf(joined, (const char *)DAT_004f9a78, dir, name);
        } else if (DAT_00587338[0] != 0) {
            igMemoryPoolView *allocator = currentAllocator();
            joined = (char *)allocator->Allocate(strlen(name) + 10);
            sprintf(joined, text_MODULES_s, name);
        } else {
            igMemoryPoolView *allocator = currentAllocator();
            char *candidate = (char *)allocator->Allocate(strlen(name) + 40);
            int i;
            if (kind == 1) {
                dirs[0] = text_usr_local_sce_iop_modules;
                dirs[1] = text_c_usr_local_sce_iop_modules;
                dirs[2] = text_c_cygwin_usr_local_sce_iop_modul;
            } else {
                dirs[0] = text_usr_local_Alchemy_iop_modules;
                dirs[1] = text_c_Alchemy_iop_modules;
                dirs[2] = 0;
            }
            for (i = 0; i < 3; i++) {
                if (dirs[i] != 0) {
                    int file;
                    sprintf(candidate, (const char *)DAT_004f9a78, dirs[i], name);
                    resolved = FUN_0032c110(candidate);
                    file = sceOpen(resolved, 1);
                    if (file < 0) {
                        Memory_FreeBufferAliasA(resolved);
                        continue;
                    }
                    sceClose(file);
                    break;
                }
            }
            Memory_FreeBufferAliasA(candidate);
            if (i == 3) {
                return 0;
            }
        }
    }
    if (resolved == 0) {
        resolved = FUN_0032c110(joined);
        Memory_FreeBufferAliasA(joined);
    }
    if ((unsigned int)strlen(resolved) > 251) {
        Memory_FreeBufferAliasA(resolved);
        return 0;
    }
    return resolved;
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
            a = ((int)StringPool_Construct((StringPool *)a));
        }
        g_stringPool[0] = a;
    }
    return g_stringPool[0];
}

static inline void setName(igPsx2FileView *object, int name) {
    int *interned = (int *)((void *)StringPool_Intern((StringPool *)(internPool()), (const char *)name));
    if (object->_prefix != 0) {
        int *header = (int *)object->_prefix - 2;
        int count = ((int *)object->_prefix)[-1] - 1;
        ((int *)object->_prefix)[-1] = count;
        if (count == 0) {
            StringChunk_ReleaseHeader((StringChunkOwnerView *)(*header), (int)header);
        }
    }
    object->_prefix = (char *)interned;
}

static inline int fileAllocator(void) {
    int a = ((int)FUN_002f8a20());
    return g_useOwnerAllocator != 0 ? a : ((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem));
}

void FUN_0032d220(void) {
    unsigned char enabled;
    FUN_00306e50(*(int *)(g_objectSystem[0] + 56), 2, (const char *)text_useOutputFilesForAtmon, (char *)&enabled, 1, 0);
    if (enabled != 0) {
        FUN_00304350(0);
        FUN_003043c0(0);
        igSmartPointer<igPsx2FileView> first((igPsx2FileView *)FUN_002d01a0(fileAllocator()));
        igSmartPointer<igPsx2FileView> second((igPsx2FileView *)FUN_002d01a0(fileAllocator()));
        if (DAT_00587338[0] != 0) {
            setName(first.p, DAT_00587358[0]);
            setName(second.p, DAT_00587358[0]);
        }
        if (first->Open(text_stdout_txt, (const char *)DAT_004f9c50) != 0) {
            FUN_00304350(first.p);
        }
        if (second->Open(text_stderr_txt, (const char *)DAT_004f9c50) != 0) {
            FUN_003043c0(second.p);
        }
    }
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

