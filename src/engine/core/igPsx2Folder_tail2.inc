igSmartPointer<igObject> igPsx2Folder_ListEntries(igPsx2Folder *self) {
    FolderEntryWide entry;
    int handle = sceDopen(self->_folderName);
    if (handle < 0) {
        /* The empty result is built with the retaining constructor: retail stores the 0 into the
         * result and re-reads it for the reference-count test. */
        return igSmartPointer<igObject>(0, kRetainReference);
    }
    igSmartPointer<igObject> list((igObject *)igStringRefList_Create(((int)igObject_GetAllocator((int)self))));
    while (sceDread(handle, &entry) != 0) {
        igStringRef text(entry.bytes + 64);
        StringList_AppendRetained(list.p, &text);
    }
    sceDclose(handle);
    return list;
}

void igPsx2Folder_TrimPath(igStringObj *path) {
    int i;
    char *s;
    int c;

    s = (char *)path->_buffer;
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

char *igPsx2_ResolveModulePath(char *name, int kind) {
    char *joined = 0;
    char *resolved = 0;
    if (kind == 0) {
        joined = (char *)Memory_Reallocate(name, currentAllocator());
    } else {
        char *dirs[3];
        const char *key;
        igSmartPointer<igObject> path((igObject *)igStringObj_Create((int)currentAllocator()));
        if (kind == 1) {
            key = text_sonyModulePath;
        } else {
            key = text_intrinsicModulePath;
        }
        if (igRegistry_GetValueStringObj(*(int *)(g_objectSystem[0] + 56), 2, key, (igStringObj **)&path, (const char *)emptyString_4, 0) != 0) {
            igPsx2Folder_TrimPath((igStringObj *)path.p);
            char *dir = (char *)((igStringObj *)path.p)->_buffer;
            dir = (dir == 0) ? g_stringObjEmptyText[0] : dir;
            igMemoryPoolView *allocator = currentAllocator();
            joined = (char *)allocator->Allocate(strlen(dir) + strlen(name) + 2);
            sprintf(joined, (const char *)percent_s_slash_percent_s, dir, name);
        } else if (g_igPsx2_useCdrom[0] != 0) {
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
                    sprintf(candidate, (const char *)percent_s_slash_percent_s, dirs[i], name);
                    resolved = igPsx2File_MakeCompletePath(candidate);
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
        resolved = igPsx2File_MakeCompletePath(joined);
        Memory_FreeBufferAliasA(joined);
    }
    if ((unsigned int)strlen(resolved) > 251) {
        Memory_FreeBufferAliasA(resolved);
        return 0;
    }
    return resolved;
}

igResult igPsx2_LoadIopModule(char *name, int kind, int argLength, const char *args) {
    int moduleId;
    return igPsx2_LoadIopModuleEx(name, kind, argLength, args, &moduleId);
}

/* Resolves the module path, loads it over SIF (retrying cdrom loads until they succeed) and
 * returns the IOP module id through moduleId. */
igResult igPsx2_LoadIopModuleEx(char *name, int kind, int argLength, const char *args, int *moduleId) {
    int id;
    char *path;

    if (argLength > 0xFB) {
        return g_resultFailure;
    }
    path = igPsx2_ResolveModulePath(name, kind);
    if (path == 0) {
        return g_resultFailure;
    }
    if (*path == 'c') {
        do {
            id = sceSifLoadModule(path, argLength, args);
        } while (id < 0);
    } else {
        id = sceSifLoadModule(path, argLength, args);
    }
    if (id < 0) {
        Memory_FreeBufferAliasA(path);
        return g_resultFailure;
    }
    *moduleId = id;
    Memory_FreeBufferAliasA(path);
    return g_resultSuccess;
}

void FUN_0032d070(void)
{
}

void igPsx2_RebootIop(void) {
    int n;
    int device;
    sceDmaReset(1);
    if (g_igPsx2_iopImagePath[0] != 0) {
        sceSifInitRpc(0);
        if (g_igPsx2_useCdrom[0] != 0) {
            sceCdInit(0);
        }
        if (g_igPsx2_loadFileModule[0] != 0) {
            while (sceSifLoadModule(g_igPsx2_loadFileModule[0], 0, 0) < 0) {
            }
        }
        while (((sceSifRebootIop(g_igPsx2_iopImagePath[0]) != 0) ^ 1)) {
        }
        while (((sceSifSyncIop() != 0) ^ 1)) {
        }
        g_igPsx2_resetIopServices = 1;
    }
    if (g_igPsx2_resetIopServices != 0) {
        sceSifInitRpc(0);
        if (g_igPsx2_loadFileModule[0] != 0) {
            sceSifLoadFileReset();
        }
        sceFsReset();
        device = g_igPsx2_useCdrom[0];
        if (device == 1 || device == 0) {
            sceCdInit(0);
            sceCdMmode(1);
        } else if (device == 2) {
            sceCdInit(0);
            sceCdMmode(2);
        }
        sceSifInitCmd();
        n = g_igPsx2_sifCmdBufferCount[0];
        sceSifSetCmdBuffer(((int)Memory_SystemAllocate(n * 12)), n);
    }
}

void igPsx2_InitializeIop(void) {
    FUN_0032d070();
    igPsx2_RebootIop();
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
            StringChunk_ReleaseHeader((StringChunk *)(*header), (int)header);
        }
    }
    object->_prefix = (char *)interned;
}

static inline int fileAllocator(void) {
    int a = ((int)Memory_GetCurrentAllocator());
    return g_useOwnerAllocator != 0 ? a : ((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem));
}

void igPsx2_SetupOutputFiles(void) {
    unsigned char enabled;
    igRegistry_GetValueBool(*(int *)(g_objectSystem[0] + 56), 2, (const char *)text_useOutputFilesForAtmon, (char *)&enabled, 1, 0);
    if (enabled != 0) {
        igReport_SetOutputFile(0);
        igReport_SetErrorFile(0);
        igSmartPointer<igPsx2FileView> first((igPsx2FileView *)igPsx2File_Create(fileAllocator()));
        igSmartPointer<igPsx2FileView> second((igPsx2FileView *)igPsx2File_Create(fileAllocator()));
        if (g_igPsx2_useCdrom[0] != 0) {
            setName(first.p, g_igPsx2_atfilePrefix[0]);
            setName(second.p, g_igPsx2_atfilePrefix[0]);
        }
        if (first->Open(text_stdout_txt, (const char *)text_wb) != 0) {
            igReport_SetOutputFile(first.p);
        }
        if (second->Open(text_stderr_txt, (const char *)text_wb) != 0) {
            igReport_SetErrorFile(second.p);
        }
    }
}

void igPsx2_SetAtfilePrefix(int *result, char *text) {
    int length;
    char *cursor;

    if ((text != 0) && (strncasecmp(text, &text_atfile[0], 7) == 0)) {
        cursor = text + 7;
        do {
            cursor += 1;
        } while (*cursor != 0x2C);
        length = (cursor - text) + 1;
        g_igPsx2_atfilePrefix[0] = ((int)Memory_SystemAllocate(length + 1));
        strncpy(g_igPsx2_atfilePrefix[0], text, length);
        *(char *)(g_igPsx2_atfilePrefix[0] + length) = 0;
        g_igPsx2File_defaultPrefix[0] = g_igPsx2_atfilePrefix[0];
        igPsx2Media_SetDevicePrefix(g_igPsx2_atfilePrefix[0]);
        *result = g_resultSuccess.v;
    } else {
        *result = g_resultFailure.v;
    }
}

