struct FolderObject { int vt; int refCount; };
struct FolderPathText : FolderObject { char *text; };
class FolderAllocator { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual char *Allocate(int); };
struct FolderSearchList;
extern "C" {
extern unsigned char g_useOwnerAllocator;
extern int DAT_00587028;
extern int DAT_00587060;
extern char *DAT_00586dc8;
extern int DAT_00587338;
extern char DAT_004ffbf8[];
extern char DAT_004ffc10[];
extern char DAT_004ffc28[];
extern char DAT_004ffc40[];
extern char DAT_004ffc60[];
extern char DAT_004ffc80[];
extern char DAT_004ffcb0[];
extern char DAT_004ffcd0[];
extern char DAT_004f7910[];
extern char DAT_004f9a78[];
extern char *DAT_004c22f0;
FolderAllocator *Memory_GetAllocatorBySelector(int);
char *FUN_002ed5a0(char *, FolderAllocator *);
FolderObject *FUN_002b9500(FolderAllocator *);
int FUN_00306770(char *, int, char *, void *, char *, int);
void FUN_0032cac0(FolderObject *);
unsigned int strlen(const char *);
int sprintf(char *, const char *, ...);
char *FUN_0032c110(char *);
int FUN_0010f330(char *, int);
void FUN_0010f5b8(int);
void Memory_FreeBufferAliasA(char *);
void igObject_Destroy(FolderObject *);
char *FUN_0032cb50(char *name, int kind);
}
struct FolderObjectRef {
    FolderObject *obj;
    FolderObjectRef() {}
    ~FolderObjectRef() {
        FolderObject *object = obj;
        if (object) {
            --object->refCount;
            if (((unsigned long long)(long long)object->refCount & 0x7fffffULL) == 0) {
                igObject_Destroy(object);
            }
        }
    }
};
static inline FolderAllocator *currentAllocator(void) {
    if (g_useOwnerAllocator != 0) {
        return Memory_GetAllocatorBySelector(DAT_00587028);
    }
    return Memory_GetAllocatorBySelector(DAT_00587060);
}
char *FUN_0032cb50(char *name, int kind) {
    char *joined = 0;
    char *resolved = 0;
    if (kind == 0) {
        joined = FUN_002ed5a0(name, currentAllocator());
    } else {
        FolderObjectRef path;
        char *dirs[3];
        char *key;
        path.obj = FUN_002b9500(currentAllocator());
        if (kind == 1) {
            key = DAT_004ffbf8;
        } else {
            key = DAT_004ffc10;
        }
        if (FUN_00306770(*(char **)(DAT_00586dc8 + 56), 2, key, &path, DAT_004f7910, 0) != 0) {
            FUN_0032cac0(path.obj);
            char *dir = ((FolderPathText *)path.obj)->text;
            dir = (dir == 0) ? DAT_004c22f0 : dir;
            FolderAllocator *allocator = currentAllocator();
            joined = allocator->Allocate(strlen(dir) + strlen(name) + 2);
            sprintf(joined, DAT_004f9a78, dir, name);
        } else if (DAT_00587338 != 0) {
            FolderAllocator *allocator = currentAllocator();
            joined = allocator->Allocate(strlen(name) + 10);
            sprintf(joined, DAT_004ffc28, name);
        } else {
            FolderAllocator *allocator = currentAllocator();
            char *candidate = allocator->Allocate(strlen(name) + 40);
            int i;
            if (kind == 1) {
                dirs[0] = DAT_004ffc40;
                dirs[1] = DAT_004ffc60;
                dirs[2] = DAT_004ffc80;
            } else {
                dirs[0] = DAT_004ffcb0;
                dirs[1] = DAT_004ffcd0;
                dirs[2] = 0;
            }
            for (i = 0; i < 3; i++) {
                if (dirs[i] != 0) {
                    int file;
                    sprintf(candidate, DAT_004f9a78, dirs[i], name);
                    resolved = FUN_0032c110(candidate);
                    file = FUN_0010f330(resolved, 1);
                    if (file < 0) {
                        Memory_FreeBufferAliasA(resolved);
                        continue;
                    }
                    FUN_0010f5b8(file);
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
    if (strlen(resolved) > 251) {
        Memory_FreeBufferAliasA(resolved);
        return 0;
    }
    return resolved;
}
