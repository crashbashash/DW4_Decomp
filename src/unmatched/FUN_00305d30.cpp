class IniPathObject;
struct IniPathHandle { IniPathObject *p; IniPathHandle() {} IniPathHandle(const IniPathHandle &o) { p = o.p; } };
class IniPathObject { public:
 virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); 
 virtual IniPathHandle Join(char *);
 int _refCount; char *text;
};
class IniSourceFile { public:
 virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); 
 virtual int Open(char *, char *);
 virtual void Close();
};
struct IniReaderView { char pad[12]; IniSourceFile *file; };
extern "C" {
IniPathObject *FUN_002c43b0(int);
char *FUN_002d1c20(void *);
char *FUN_002d1c30(void *);
int FUN_002eb010(int);
void FUN_003077a0(IniReaderView *);
void FUN_00307870(IniReaderView *, IniSourceFile *, int);
void StringChunk_ReleaseHeader(int, int *);
int StringPool_Construct(int);
char *StringPool_Intern(int, char *);
void igObject_Destroy(void *);
int igObject_GetAllocator(void *);
int strlen(char *);
extern char *DAT_004c22f0;
extern char DAT_004f9478[];
extern char DAT_004f96a8[];
extern void *DAT_00586dc8;
extern int DAT_00586f20;
}
static inline int pool() {
    if (DAT_00586f20 == 0) {
        int p = FUN_002eb010(0x10);
        if (p != 0) { p = StringPool_Construct(p); }
        DAT_00586f20 = p;
    }
    return DAT_00586f20;
}
static inline void dropString(char *s) {
    if (s != 0) {
        int *hd = (int *)(s - 8);
        int rc = ((int *)s)[-1] - 1;
        ((int *)s)[-1] = rc;
        if (rc == 0) { StringChunk_ReleaseHeader(*hd, hd); }
    }
}
static inline void assign(char **slot, char *text) {
    char *v = StringPool_Intern(pool(), text);
    char *old = *slot;
    dropString(old);
    *slot = v;
}
static inline void setText(IniPathObject *o, char *text) {
    char *v = StringPool_Intern(pool(), text);
    char *old = o->text;
    dropString(old);
    o->text = v;
}
static inline void dropPath(IniPathObject *o) {
    if (o != 0) {
        o->_refCount = o->_refCount - 1;
        if (((unsigned long long)((long long)o->_refCount << 0x29) >> 0x29) == 0) { igObject_Destroy(o); }
    }
}
static inline char *pathText(IniPathObject *s) { char *t = s->text; if (t == 0) { return DAT_004c22f0; } return t; }
static inline int tryPath(IniReaderView *self, IniPathObject *base, char *name) {
    IniPathHandle joined = base->Join(name);
    IniSourceFile *file = self->file;
    int found = file->Open(pathText(joined.p), DAT_004f96a8);
    IniPathObject *held = joined.p;
    if (held != 0) {
        held->_refCount = held->_refCount - 1;
        held = *(IniPathObject *volatile *)&joined.p;
        if (((unsigned long long)((long long)held->_refCount << 0x29) >> 0x29) == 0) { igObject_Destroy(held); }
    }
    return found;
}
extern "C" bool FUN_00305d30(IniReaderView *self, char *name, char *dir) {
    char *held;
    char *interned;
    int found;
    IniPathObject *base;
    IniPathObject *other;
    char *second;
    if (name == 0) {
        interned = 0;
    } else {
        interned = StringPool_Intern(pool(), name);
    }
    *(char *volatile *)&held = interned;
    if (held == 0 || strlen(held) == 0) {
        assign(&held, DAT_004f9478);
    }
    found = self->file->Open(held, DAT_004f96a8);
    if (found == 0) {
        if (dir == 0 || strlen(dir) == 0) {
            dir = FUN_002d1c20(DAT_00586dc8);
        }
        if (dir != 0 && strlen(dir) != 0) {
            *(IniPathObject *volatile *)&base = FUN_002c43b0(igObject_GetAllocator(self));
            setText(base, dir);
            found = tryPath(self, base, held);
            dropPath(base);
        }
    }
    if (found == 0) {
        *(IniPathObject *volatile *)&other = FUN_002c43b0(igObject_GetAllocator(self));
        second = FUN_002d1c30(DAT_00586dc8);
        setText(other, second);
        found = tryPath(self, other, held);
        dropPath(other);
    }
    if (found == 0) {
        dropString(held);
        return false;
    }
    FUN_003077a0(self);
    FUN_00307870(self, self->file, 1);
    self->file->Close();
    dropString(held);
    return true;
}
