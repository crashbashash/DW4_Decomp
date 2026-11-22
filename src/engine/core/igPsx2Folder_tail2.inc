namespace Gap {
namespace Core {

igSmartPointer<igStringRefList> igPsx2Folder::getFilesAndSubFolders() const
{
    FolderEntryWide entry;
    int handle = sceDopen(_folderName.p);
    if (handle < 0) {
        /* The empty result is built with the retaining constructor: retail stores the 0 into the
         * result and re-reads it for the reference-count test. */
        return igSmartPointer<igStringRefList>((igStringRefList *)0, kRetainReference);
    }
    igSmartPointer<igStringRefList> list((igStringRefList *)igStringRefList_Create((int)getMemoryPool()));
    while (sceDread(handle, &entry) != 0) {
        igStringRef text(entry.bytes + 64);
        StringList_AppendRetained(list.p, (char *const *)&text);
    }
    sceDclose(handle);
    return list;
}

void igPsx2Folder::trimPath(igStringObj *path) {
    int i;
    char *s;
    int c;

    s = (char *)path->_buffer;
    if (s == 0) {
        s = g_stringObjEmptyText;
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
}
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
            key ="sonyModulePath";
        } else {
            key ="intrinsicModulePath";
        }
        if (((Gap::Core::igRegistry *)g_objectSystem->configRegistry)->getValue(2, key, *(igStringObjRef *)&path, (const char *)"", 0)) {
            Gap::Core::igPsx2Folder::trimPath((igStringObj *)path.p);
            char *dir = (char *)((igStringObj *)path.p)->_buffer;
            dir = (dir == 0) ? g_stringObjEmptyText : dir;
            igMemoryPoolView *allocator = currentAllocator();
            joined = (char *)allocator->Allocate(strlen(dir) + strlen(name) + 2);
            sprintf(joined, (const char *)"%s/%s", dir, name);
        } else if (g_igPsx2_useCdrom != 0) {
            igMemoryPoolView *allocator = currentAllocator();
            joined = (char *)allocator->Allocate(strlen(name) + 10);
            sprintf(joined,"\\MODULES\\%s", name);
        } else {
            igMemoryPoolView *allocator = currentAllocator();
            char *candidate = (char *)allocator->Allocate(strlen(name) + 40);
            int i;
            if (kind == 1) {
                dirs[0] ="/usr/local/sce/iop/modules";
                dirs[1] ="c:/usr/local/sce/iop/modules";
                dirs[2] ="c:/cygwin/usr/local/sce/iop/modules";
            } else {
                dirs[0] ="/usr/local/Alchemy/iop/modules";
                dirs[1] ="c:/Alchemy/iop/modules";
                dirs[2] = 0;
            }
            for (i = 0; i < 3; i++) {
                if (dirs[i] != 0) {
                    int file;
                    sprintf(candidate, (const char *)"%s/%s", dirs[i], name);
                    resolved = Gap::Core::igPsx2File::makeCompletePath(candidate);
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
        resolved = Gap::Core::igPsx2File::makeCompletePath(joined);
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

int g_igPsx2_sifCmdBufferCount = 5;
unsigned char g_igPsx2_resetIopServices = 1;
const char *g_igPsx2_iopImagePath;
char *g_igPsx2_loadFileModule;

void igPsx2_RebootIop(void) {
    int n;
    int device;
    sceDmaReset(1);
    if (g_igPsx2_iopImagePath != 0) {
        sceSifInitRpc(0);
        if (g_igPsx2_useCdrom != 0) {
            sceCdInit(0);
        }
        if (g_igPsx2_loadFileModule != 0) {
            while (sceSifLoadModule(g_igPsx2_loadFileModule, 0, 0) < 0) {
            }
        }
        while (((sceSifRebootIop(g_igPsx2_iopImagePath) != 0) ^ 1)) {
        }
        while (((sceSifSyncIop() != 0) ^ 1)) {
        }
        g_igPsx2_resetIopServices = 1;
    }
    if (g_igPsx2_resetIopServices != 0) {
        sceSifInitRpc(0);
        if (g_igPsx2_loadFileModule != 0) {
            sceSifLoadFileReset();
        }
        sceFsReset();
        device = g_igPsx2_useCdrom;
        if (device == 1 || device == 0) {
            sceCdInit(0);
            sceCdMmode(1);
        } else if (device == 2) {
            sceCdInit(0);
            sceCdMmode(2);
        }
        sceSifInitCmd();
        n = g_igPsx2_sifCmdBufferCount;
        sceSifSetCmdBuffer((sceSifCmdData *)Memory_SystemAllocate(n * 12), n);
    }
}

void igPsx2_InitializeIop(void) {
    FUN_0032d070();
    igPsx2_RebootIop();
}

/* matching construct: assigning `_prefix = name` computes the member's address into a register first; retail reads it
 * through the file */
static inline void setPrefix(Gap::Core::igPsx2File *file, const char *name) {
    char *interned = (char *)StringPool_Intern(InternedStrings::get(), name);
    releaseString(file->_prefix.p);
    file->_prefix.p = interned;
}

static inline igMemoryPoolView *fileAllocator(void) {
    igMemoryPoolView *a = (igMemoryPoolView *)Memory_GetCurrentAllocator();
    return g_useOwnerAllocator != 0 ? a : (igMemoryPoolView *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem);
}

void igPsx2_SetupOutputFiles(void) {
    unsigned char enabled;
    ((Gap::Core::igRegistry *)g_objectSystem->configRegistry)->getValue(2, (const char *)"useOutputFilesForAtmon", enabled, 1, 0);
    if (enabled != 0) {
        igReport_SetOutputFile(0);
        igReport_SetErrorFile(0);
        igSmartPointer<Gap::Core::igPsx2File> first(Gap::Core::igPsx2File::_instantiateFromPool(fileAllocator()));
        igSmartPointer<Gap::Core::igPsx2File> second(Gap::Core::igPsx2File::_instantiateFromPool(fileAllocator()));
        if (g_igPsx2_useCdrom != 0) {
            setPrefix(first.p, (const char *)g_igPsx2_atfilePrefix);
            setPrefix(second.p, (const char *)g_igPsx2_atfilePrefix);
        }
        if (first->fopen("stdout.txt", "wb") != 0) {
            igReport_SetOutputFile(first.p);
        }
        if (second->fopen("stderr.txt", "wb") != 0) {
            igReport_SetErrorFile(second.p);
        }
    }
}

igResult igPsx2_SetAtfilePrefix(const char *text) {
    int length;
    const char *cursor;

    if ((text != 0) && (strncasecmp(text, "atfile:", 7) == 0)) {
        cursor = text + 7;
        do {
            cursor += 1;
        } while (*cursor != 0x2C);
        length = (cursor - text) + 1;
        g_igPsx2_atfilePrefix = ((int)Memory_SystemAllocate(length + 1));
        strncpy((char *)g_igPsx2_atfilePrefix, text, length);
        *(char *)(g_igPsx2_atfilePrefix + length) = 0;
        Gap::Core::igPsx2File::defaultPrefix = (const char *)g_igPsx2_atfilePrefix;
        igPsx2Media_SetDevicePrefix(g_igPsx2_atfilePrefix);
        return g_resultSuccess;
    } else {
        return g_resultFailure;
    }
}

