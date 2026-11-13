struct FolderObject { int vt; int refCount; };
struct FolderSelf { int vt; int refCount; int path; };
struct FolderEntry { char bytes[324]; };
struct FolderFileStat { int mode; char rest[60]; };
struct FolderPathText : FolderObject { char *text; };
struct FolderStringRef;
extern "C" {
extern int DAT_00586f20;
int sceDopen(int);
int FUN_00110bf8(int);
int FUN_00110d60(int, FolderEntry *);
int StringPool_Allocate(int);
int StringPool_Construct(int);
char *StringPool_Intern(int, char *);
void StringChunk_ReleaseHeader(int, int *);
FolderObject *igStringRefList_Create(int);
FolderPathText *FUN_002b9500(int);
int FUN_0030b7e0(FolderPathText *, const char *, int, char *);
int FUN_00110eb8(const char *, FolderFileStat *);
extern char DAT_004f9a78[];
extern char *DAT_004c22f0;
int igObject_GetAllocator(FolderSelf *);
void StringList_AppendRetained(FolderObject *, FolderStringRef *);
void igObject_Destroy(FolderObject *);
}
struct FolderStringRef {
    char *text;
    FolderStringRef(char *t) : text(t) {}
    ~FolderStringRef() {
        if (text != 0) {
            int *hdr = (int *)text - 2;
            int r = ((int *)text)[-1] - 1;
            ((int *)text)[-1] = r;
            if (r == 0) {
                StringChunk_ReleaseHeader(*hdr, hdr);
            }
        }
    }
};
struct FolderObjectRef {
    FolderObject *obj;
    FolderObjectRef() {}
    FolderObjectRef(FolderObject *o) : obj(o) { if (obj != 0) { obj->refCount = obj->refCount + 1; } }
    FolderObjectRef(const FolderObjectRef &o) : obj(o.obj) { if (obj != 0) { obj->refCount = obj->refCount + 1; } }
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
extern "C" FolderObjectRef Gap__Core__igPsx2Folder__vfunc_24(FolderSelf *self);
FolderObjectRef Gap__Core__igPsx2Folder__vfunc_24(FolderSelf *self) {
    FolderEntry entry;
    FolderFileStat st;
    int handle = sceDopen(self->path);
    if (handle < 0) {
        return FolderObjectRef(0);
    }
    FolderObjectRef list;
    list.obj = igStringRefList_Create(igObject_GetAllocator(self));
    FolderObjectRef path;
    path.obj = FUN_002b9500(igObject_GetAllocator(self));
    while (FUN_00110d60(handle, &entry) != 0) {
        FUN_0030b7e0((FolderPathText *)path.obj, DAT_004f9a78, self->path, (char *)&entry + 64);
        char *full = ((FolderPathText *)path.obj)->text;
        full = (full == 0) ? DAT_004c22f0 : full;
        if (FUN_00110eb8(full, &st) != 0) {
            continue;
        }
        if ((st.mode & 0xf000) == 0x1000) {
            continue;
        }
        char *name = (entry.bytes + 64);
        char *interned;
        if (name == 0) {
            interned = 0;
        } else {
            if (DAT_00586f20 == 0) {
                int v = StringPool_Allocate(16);
                if (v != 0) {
                    v = StringPool_Construct(v);
                }
                DAT_00586f20 = v;
            }
            interned = StringPool_Intern(DAT_00586f20, name);
        }
        FolderStringRef text(interned);
        StringList_AppendRetained(list.obj, &text);
    }
    FUN_00110bf8(handle);
    return list;
}
