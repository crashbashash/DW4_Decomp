struct SrObject { int pad0; int _refCount; char *text; int length; };
struct SrList { int pad0; int _refCount; int count; char pad1[4]; char **data; };
struct SrInfo { char pad0[28]; void *types; };
class SrPassList {
public:
    virtual void d0();    virtual void d1();    virtual void d2();    virtual void d3();    virtual void d4();    virtual void d5();    virtual void d6();    virtual void d7();    virtual void d8();    virtual void d9();    virtual void d10();    virtual void d11();    virtual void d12();    virtual void d13();    virtual void d14();    virtual void d15();    virtual void d16();    virtual void d17();    virtual void d18();    virtual void d19();    virtual void d20();
    virtual void setCount(int);
    virtual void d22();
    virtual void prepare();
};
class SrTarget {
public:
    virtual void d0();    virtual void d1();    virtual void d2();    virtual void d3();    virtual void d4();    virtual void d5();    virtual void d6();    virtual void d7();    virtual void d8();    virtual void d9();    virtual void d10();    virtual void d11();    virtual void d12();    virtual void d13();    virtual void d14();    virtual void d15();    virtual void d16();    virtual void d17();    virtual void d18();    virtual void d19();    virtual void d20();    virtual void d21();    virtual void d22();    virtual void d23();    virtual void d24();    virtual void d25();    virtual void d26();    virtual void d27();    virtual void d28();
    virtual void clear();
    virtual void d30();    virtual void d31();    virtual void d32();    virtual void d33();    virtual void d34();    virtual void d35();    virtual void d36();    virtual void d37();    virtual void d38();    virtual void d39();
    virtual void setFlag(unsigned char);
    virtual void d41();    virtual void d42();
    virtual void setInfo(SrObject *);
    char pad0[32];
    SrPassList *passes;
};
struct SrProcessor { char pad0[28]; int ini; char pad1[12]; void *owner; SrInfo *info; };
struct StringCopy {
    char *text;
    StringCopy(const StringCopy &other);
};
struct StringRef {
    char *p;
    StringRef(char *text) : p(text) {}
    StringRef(const StringRef &other);
    ~StringRef();
};
struct SrDrop {
    static inline void release(SrObject *o);
};
struct ReturnedRef {
    SrObject *p;
    ReturnedRef(const ReturnedRef &other);
    ~ReturnedRef();
};
struct TextRef {
    SrObject *p;
    TextRef(SrObject *object) : p(object) {}
    ~TextRef();
};
extern "C" {
int FUN_00306360(int, char *, int);
StringRef FUN_001c6fa0(SrProcessor *);
void FUN_001cb1f0(SrProcessor *, char *, int, int, int, void *);
void FUN_001cb2d0(SrProcessor *, void *, void *, SrTarget *);
unsigned char FUN_00306910(int, int, void *, StringRef *, void *, int);
void *igObject_GetAllocator(void *);
SrList *FUN_002b90e0(void *);
unsigned char FUN_00306aa0(int, int, void *, SrList *, int);
ReturnedRef FUN_001ca6c0(SrProcessor *, char *, int);
SrObject *FUN_002b9500(void *);
StringRef FUN_001ccb20(SrList *);
void FUN_0030b3c0(SrObject *, void *);
int FUN_0012a78c(void *);
void FUN_0030b460(SrObject *, void *, int, int);
unsigned char FUN_00306770(int, int, char *, TextRef *, void *, int);
void *FUN_002eb010(int);
void *FUN_002eadf0(void *);
char *FUN_002eaf60(void *, char *);
void FUN_001ca620(SrList *, const StringRef &);
StringCopy StringList_CopyRetained(SrList *, int);
void List_RemoveWordAt(SrList *, int);
SrObject *FUN_00198b60(void *);
int FUN_00306e50(int, int, void *, unsigned char *, int, int);
void FUN_001d9090(SrTarget *, int, int);
ReturnedRef FUN_001c8c80(SrProcessor *, int, void *, void *, SrList *);
void FUN_001cade0(SrProcessor *, SrObject *, SrObject *, SrList *, SrList *, SrList *);
void FUN_001d86f0(SrPassList *, int, SrObject *);
void FUN_001d87b0(SrPassList *, int, SrObject *);
void FUN_001d8870(SrPassList *, int, SrObject *);
void StringChunk_ReleaseHeader(int, int *);
void igObject_Destroy(void *);
int igObject_IsKindOf(void *, void *);
extern char *DAT_004c22f0[4];
extern int DAT_004e4660[4];
extern int DAT_004e4658[2];
extern int DAT_004e4690[4];
extern int DAT_004e46c0[4];
extern int DAT_004e46e8[4];
extern int DAT_004e4700[2];
extern int DAT_004e4720[4];
extern int DAT_004e4738[4];
extern int DAT_004e4748[2];
extern int DAT_004e4750[4];
extern int DAT_004e4760[4];
extern int DAT_004e4778[4];
extern int DAT_004e4788[4];
extern int DAT_004e4798[4];
extern void *DAT_0055f460[4];
extern void *DAT_00561830[4];
extern void *DAT_00586f20;
}
static inline void releaseString(char *s) {
    if (s != 0) {
        int *h = (int *)s - 2;
        int c = ((int *)s)[-1] - 1;
        ((int *)s)[-1] = c;
        if (c == 0) {
            StringChunk_ReleaseHeader(*h, h);
        }
    }
}
static inline SrObject *asMaterial(SrObject *o) {
    if (o != 0 && igObject_IsKindOf(o, DAT_0055f460[0]) != 0) {
        return o;
    }
    return 0;
}
static inline SrObject *asTexture(SrObject *o) {
    if (o != 0 && igObject_IsKindOf(o, DAT_00561830[0]) != 0) {
        return o;
    }
    return 0;
}
static inline char *textOf(SrObject *o) {
    char *t = o->text;
    return (t == 0) ? DAT_004c22f0[0] : t;
}
inline StringRef::~StringRef() {
    if (p != 0) {
        int *h = (int *)p - 2;
        int c = ((int *)p)[-1] - 1;
        ((int *)p)[-1] = c;
        if (c == 0) {
            StringChunk_ReleaseHeader(*h, h);
        }
    }
}
inline ReturnedRef::ReturnedRef(const ReturnedRef &other) : p(other.p) {
    if (p != 0) p->_refCount = p->_refCount + 1;
}
inline ReturnedRef::~ReturnedRef() {
    if (p != 0) {
        p->_refCount = p->_refCount - 1;
        if ((p->_refCount & 0x7FFFFF) == 0) igObject_Destroy(p);
    }
}
inline TextRef::~TextRef() {
    SrObject *o;
    if ((o = p) != 0) {
        o->_refCount = o->_refCount - 1;
        if ((o->_refCount & 0x7FFFFF) == 0) igObject_Destroy(o);
    }
}
template <class T> struct igSmartPointer {
    T *p;
    igSmartPointer() : p(0) {}
    T *get() const { return p; }
    igSmartPointer(T *object) : p(object) {
        if (p != 0) p->_refCount = p->_refCount + 1;
    }
    ~igSmartPointer() {
        T *o = p;
        if (o != 0) {
            o->_refCount = o->_refCount - 1;
            if ((o->_refCount & 0x7FFFFF) == 0) igObject_Destroy(o);
        }
    }
    void set(T *held) {
        T *o;
        if (held != 0) held->_refCount = held->_refCount + 1;
        if ((o = p) != 0) {
            o->_refCount = o->_refCount - 1;
            if ((o->_refCount & 0x7FFFFF) == 0) igObject_Destroy(o);
        }
        p = held;
    }
    void operator=(const ReturnedRef &other) {
        T *held = other.p;
        T *o;
        if (held != 0) held->_refCount = held->_refCount + 1;
        if ((o = p) != 0) {
            o->_refCount = o->_refCount - 1;
            if ((o->_refCount & 0x7FFFFF) == 0) igObject_Destroy(o);
        }
        p = held;
    }
};
static inline void removeFirst(SrList *p) {
    {
        StringCopy removed = StringList_CopyRetained(p, 0);
        releaseString(removed.text);
        releaseString(removed.text);
    }
    List_RemoveWordAt(p, 0);
    ((int *)p->data)[p->count] = 0;
}
struct ListRef {
    SrList *p;
    ListRef(SrList *object) : p(object) {}
    ~ListRef() {
        SrList *o;
        if ((o = p) != 0) {
            o->_refCount = o->_refCount - 1;
            if ((o->_refCount & 0x7FFFFF) == 0) igObject_Destroy(o);
        }
    }
};
extern "C" int FUN_001cb340(SrProcessor *self, SrTarget *target, int arg) {
    unsigned char flag;
    SrPassList *passes;
    int i;
    int infoSection;
    int count;
    int pass;
    SrObject *held;
    int section;
    passes = target->passes;
    passes->prepare();
    target->clear();
    section = FUN_00306360(self->ini, (char *)DAT_004e4690, 0);
    if (section == -1) {
        return 0;
    }
    StringRef baseName = FUN_001c6fa0(self);
    if (baseName.p != 0) {
        FUN_001cb1f0(self, baseName.p, self->ini, section, arg, self->info->types);
    }
    FUN_001cb2d0(self, self->info->types, DAT_004e4720, target);
    StringRef defaultName((char *)0);
    if (FUN_00306910(self->ini, section, DAT_004e4738, &defaultName, DAT_004e4660, 0) == 0) {
        return 0;
    }
    section = FUN_00306360(self->ini, defaultName.p, 0);
    if (section == -1) {
        return 0;
    }
    ListRef names(FUN_002b90e0(igObject_GetAllocator(self)));
    if (FUN_00306aa0(self->ini, section, DAT_004e4748, names.p, 0) == 0) {
        return 0;
    }
    StringRef infoName((char *)0);
    igSmartPointer<SrObject> info;
    ListRef keys(FUN_002b90e0(igObject_GetAllocator(self)));
    ListRef values(FUN_002b90e0(igObject_GetAllocator(self)));
    count = names.p->count;
    if (FUN_00306910(self->ini, section, DAT_004e4750, &infoName, DAT_004e4660, 0) != 0) {
        infoSection = FUN_00306360(self->ini, infoName.p, 0);
        info = ReturnedRef(FUN_001ca6c0(self, infoName.p, 1));
        ListRef pending(FUN_002b90e0(igObject_GetAllocator(self)));
        FUN_00306aa0(self->ini, infoSection, DAT_004e4700, pending.p, 0);
        TextRef value(FUN_002b9500(igObject_GetAllocator(self)));
        TextRef key(FUN_002b9500(igObject_GetAllocator(self)));
        while (pending.p->count != 0) {
            int ok;
            FUN_0030b3c0(key.p, FUN_001ccb20(pending.p).p);
            {
                SrObject *k = key.p;
                int length = k->length;
                FUN_0030b460(k, DAT_004e46c0, length, FUN_0012a78c(DAT_004e46c0));
            }
            FUN_0030b3c0(value.p, DAT_004e4660);
            {
                char *t = key.p->text;
                int ini = self->ini;
                t = (t == 0) ? DAT_004c22f0[0] : t;
                ok = FUN_00306770(ini, infoSection, t, &value, DAT_004e4660, 0);
            }
            if (ok == 0) {
                FUN_0030b3c0(key.p, FUN_001ccb20(pending.p).p);
                {
                    SrObject *k = key.p;
                    int length = k->length;
                    FUN_0030b460(k, DAT_004e46e8, length, FUN_0012a78c(DAT_004e46e8));
                }
                FUN_0030b3c0(value.p, DAT_004e4660);
                {
                    char *t = key.p->text;
                    int ini = self->ini;
                    t = (t == 0) ? DAT_004c22f0[0] : t;
                    ok = FUN_00306770(ini, infoSection, t, &value, DAT_004e4660, 0);
                }
            }
            if (ok != 0) {
                char *text = textOf(value.p);
                char *h;
                if (text == 0) {
                    h = 0;
                } else {
                    if (DAT_00586f20 == 0) {
                        void *table = FUN_002eb010(16);
                        if (table != 0) {
                            table = FUN_002eadf0(table);
                        }
                        DAT_00586f20 = table;
                    }
                    h = FUN_002eaf60(DAT_00586f20, text);
                }
                FUN_001ca620(keys.p, StringRef(h));
                FUN_001ca620(values.p, FUN_001ccb20(pending.p));
            }
            removeFirst(pending.p);
        }
    }
    if (info.p == 0) {
        void *owner = self->owner;
        {
            SrObject *o;
            if ((o = info.p) != 0) {
                o->_refCount = o->_refCount - 1;
                if ((o->_refCount & 0x7FFFFF) == 0) igObject_Destroy(o);
            }
        }
        info.p = FUN_00198b60(owner);
    }
    flag = 0;
    if (FUN_00306e50(self->ini, section, DAT_004e4760, &flag, 0, 0) != 0) {
        target->setFlag(flag);
    }
    target->setInfo(info.p);
    passes->setCount(count);
    ListRef shared(FUN_002b90e0(igObject_GetAllocator(self)));
    for (i = 0; i < count; i++) {
        FUN_001d9090(target, i, 1);
        {
            char *n = StringList_CopyRetained(names.p, i).text;
            releaseString(n);
            pass = FUN_00306360(self->ini, n, 0);
        }
        if (pass == -1) {
            return 0;
        }
        igSmartPointer<SrObject> primary((SrObject *)0);
        igSmartPointer<SrObject> second((SrObject *)0);
        igSmartPointer<SrObject> third((SrObject *)0);
        igSmartPointer<SrObject> found((SrObject *)0);
        found = FUN_001c8c80(self, pass, DAT_004e4778, DAT_0055f460[0], shared.p);
        held = found.p;
        if (held != 0) {
            primary.set(asMaterial(held));
            FUN_001cade0(self, info.p, primary.p, shared.p, keys.p, values.p);
            found = FUN_001c8c80(self, pass, DAT_004e4788, DAT_0055f460[0], shared.p);
            held = found.get();
            if (held == 0) {
                return 0;
            }
            second.set(asMaterial(held));
            FUN_001cade0(self, info.p, second.p, shared.p, keys.p, values.p);
        } else {
            found = FUN_001c8c80(self, pass, DAT_004e4658, DAT_0055f460[0], shared.p);
            held = found.get();
            if (held == 0) {
                return 0;
            }
            primary.set(asMaterial(held));
            second.set(primary.p);
            FUN_001cade0(self, info.p, primary.p, shared.p, keys.p, values.p);
        }
        found = FUN_001c8c80(self, pass, DAT_004e4798, DAT_00561830[0], shared.p);
        held = found.p;
        if (held != 0) {
            third.set(asTexture(held));
            FUN_001cade0(self, info.p, third.p, shared.p, keys.p, values.p);
        }
        FUN_001d86f0(passes, i, primary.p);
        FUN_001d87b0(passes, i, second.p);
        FUN_001d8870(passes, i, third.p);
    }
    return 1;
}
