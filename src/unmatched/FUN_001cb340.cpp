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
extern "C" {
int FUN_00306360(int, char *, int);
void FUN_001c6fa0(char **, SrProcessor *);
void FUN_001cb1f0(SrProcessor *, char *, int, int, int, void *);
void FUN_001cb2d0(SrProcessor *, void *, void *, SrTarget *);
unsigned char FUN_00306910(int, int, void *, char **, void *, int);
void *igObject_GetAllocator(void *);
SrList *FUN_002b90e0(void *);
unsigned char FUN_00306aa0(int, int, void *, SrList *, int);
void FUN_001ca6c0(SrObject **, SrProcessor *, char *, int);
SrObject *FUN_002b9500(void *);
void FUN_001ccb20(char **, SrList *);
void FUN_0030b3c0(SrObject *, void *);
int FUN_0012a78c(void *);
void FUN_0030b460(SrObject *, void *, int, int);
unsigned char FUN_00306770(int, int, char *, SrObject **, void *, int);
void *FUN_002eb010(int);
void *FUN_002eadf0(void *);
char *FUN_002eaf60(void *, char *);
void FUN_001ca620(SrList *, char **);
void StringList_CopyRetained(char **, SrList *, int);
void List_RemoveWordAt(SrList *, int);
SrObject *FUN_00198b60(void *);
int FUN_00306e50(int, int, void *, unsigned char *, int, int);
void FUN_001d9090(SrTarget *, int, int);
void FUN_001c8c80(SrObject **, SrProcessor *, int, void *, void *, SrList *);
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
#define SLOT(T, x) (*(T *volatile *)&(x))
#define ADD(o) do { if (o != 0) { o->_refCount = o->_refCount + 1; } } while (0)
#define DROP(T, x) \
    do { \
        T *o_ = (x); \
        if (o_ != 0) { \
            o_->_refCount = o_->_refCount - 1; \
            if (((unsigned long long)((long long)(int)o_->_refCount << 0x29) >> 0x29) == 0) { \
                igObject_Destroy(o_); \
            } \
        } \
    } while (0)
#define DROP_TEMP(x) \
    do { \
        if (x != 0) { \
            x->_refCount = (int)x->_refCount - 1; \
            if (((unsigned long long)((long long)(int)x->_refCount << 0x29) >> 0x29) == 0) { \
                igObject_Destroy(x); \
            } \
        } \
    } while (0)
#define SET_REF(slot, value) \
    do { \
        held = (value); \
        ADD(held); \
        DROP(SrObject, slot); \
        SLOT(SrObject, slot) = held; \
    } while (0)
#define FETCH(temp, key, meta) \
    do { \
        FUN_001c8c80(&temp, self, pass, key, meta, shared); \
        held = temp; \
        ADD(held); \
        DROP(SrObject, found); \
        SLOT(SrObject, found) = held; \
        DROP_TEMP(temp); \
    } while (0)
#define END_LISTS() \
    do { \
        DROP(SrList, shared); \
        DROP(SrList, values); \
        DROP(SrList, keys); \
        DROP(SrObject, info); \
        releaseString(infoName); \
        DROP(SrList, names); \
        releaseString(defaultName); \
        releaseString(baseName); \
    } while (0)
#define END_REFS() \
    do { \
        DROP(SrObject, found); \
        DROP(SrObject, third); \
        DROP(SrObject, second); \
        DROP(SrObject, primary); \
    } while (0)
extern "C" int FUN_001cb340(SrProcessor *self, SrTarget *target, int arg) {
    unsigned char flag;
    char *baseName;
    char *defaultName;
    SrList *names;
    char *infoName;
    SrObject *info;
    SrList *keys;
    SrList *values;
    SrList *pending;
    SrObject *value;
    SrObject *key;
    SrList *shared;
    SrObject *primary;
    SrObject *second;
    SrObject *third;
    SrObject *found;
    SrObject *loaded;
    SrObject *loadedCopy;
    char *entry;
    char *alternate;
    char *hashed;
    char *entryAgain;
    char *nameCopy;
    SrObject *t160;
    SrObject *t156;
    SrObject *t152;
    SrObject *t148;
    char *removed;
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
    FUN_001c6fa0(&baseName, self);
    if (baseName != 0) {
        FUN_001cb1f0(self, baseName, self->ini, section, arg, self->info->types);
    }
    FUN_001cb2d0(self, self->info->types, DAT_004e4720, target);
    defaultName = 0;
    if (FUN_00306910(self->ini, section, DAT_004e4738, &defaultName, DAT_004e4660, 0) == 0) {
        releaseString(defaultName);
        releaseString(baseName);
        return 0;
    }
    section = FUN_00306360(self->ini, defaultName, 0);
    if (section == -1) {
        releaseString(defaultName);
        releaseString(baseName);
        return 0;
    }
    SLOT(SrList, names) = FUN_002b90e0(igObject_GetAllocator(self));
    if (FUN_00306aa0(self->ini, section, DAT_004e4748, names, 0) == 0) {
        DROP(SrList, names);
        releaseString(defaultName);
        releaseString(baseName);
        return 0;
    }
    infoName = 0;
    SLOT(SrObject, info) = 0;
    SLOT(SrList, keys) = FUN_002b90e0(igObject_GetAllocator(self));
    SLOT(SrList, values) = FUN_002b90e0(igObject_GetAllocator(self));
    count = names->count;
    if (FUN_00306910(self->ini, section, DAT_004e4750, &infoName, DAT_004e4660, 0) != 0) {
        infoSection = FUN_00306360(self->ini, infoName, 0);
        FUN_001ca6c0(&loaded, self, infoName, 1);
        SLOT(SrObject, loadedCopy) = loaded;
        { SrObject *a_ = loadedCopy; ADD(a_); }
        held = loadedCopy;
        ADD(held);
        DROP(SrObject, info);
        SLOT(SrObject, info) = held;
        DROP_TEMP(loadedCopy);
        DROP_TEMP(loaded);
        SLOT(SrList, pending) = FUN_002b90e0(igObject_GetAllocator(self));
        FUN_00306aa0(self->ini, infoSection, DAT_004e4700, pending, 0);
        SLOT(SrObject, value) = FUN_002b9500(igObject_GetAllocator(self));
        SLOT(SrObject, key) = FUN_002b9500(igObject_GetAllocator(self));
        while (pending->count != 0) {
            int ok;
            FUN_001ccb20(&entry, pending);
            FUN_0030b3c0(key, entry);
            releaseString(entry);
            {
                SrObject *k = key;
                int length = k->length;
                FUN_0030b460(k, DAT_004e46c0, length, FUN_0012a78c(DAT_004e46c0));
            }
            FUN_0030b3c0(value, DAT_004e4660);
            {
                char *t = key->text;
                int ini = self->ini;
                t = (t == 0) ? DAT_004c22f0[0] : t;
                ok = FUN_00306770(ini, infoSection, t, &value, DAT_004e4660, 0);
            }
            if (ok == 0) {
                FUN_001ccb20(&alternate, pending);
                FUN_0030b3c0(key, alternate);
                releaseString(alternate);
                {
                    SrObject *k = key;
                    int length = k->length;
                    FUN_0030b460(k, DAT_004e46e8, length, FUN_0012a78c(DAT_004e46e8));
                }
                FUN_0030b3c0(value, DAT_004e4660);
                {
                    char *t = key->text;
                    int ini = self->ini;
                    t = (t == 0) ? DAT_004c22f0[0] : t;
                    ok = FUN_00306770(ini, infoSection, t, &value, DAT_004e4660, 0);
                }
            }
            if (ok != 0) {
                char *text = textOf(value);
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
                hashed = h;
                FUN_001ca620(keys, &hashed);
                releaseString(hashed);
                FUN_001ccb20(&entryAgain, pending);
                FUN_001ca620(values, &entryAgain);
                releaseString(entryAgain);
            }
            {
                SrList *p = pending;
                StringList_CopyRetained(&removed, p, 0);
                releaseString(removed);
                releaseString(removed);
                List_RemoveWordAt(p, 0);
                ((int *)p->data)[p->count] = 0;
            }
        }
        DROP(SrObject, key);
        DROP(SrObject, value);
        DROP(SrList, pending);
    }
    if (info == 0) {
        void *owner = self->owner;
        DROP(SrObject, info);
        SLOT(SrObject, info) = FUN_00198b60(owner);
    }
    flag = 0;
    if (FUN_00306e50(self->ini, section, DAT_004e4760, &flag, 0, 0) != 0) {
        target->setFlag(flag);
    }
    target->setInfo(info);
    passes->setCount(count);
    SLOT(SrList, shared) = FUN_002b90e0(igObject_GetAllocator(self));
    for (i = 0; i < count; i++) {
        FUN_001d9090(target, i, 1);
        StringList_CopyRetained(&nameCopy, names, i);
        {
            char *n = nameCopy;
            releaseString(n);
            pass = FUN_00306360(self->ini, n, 0);
        }
        if (pass == -1) {
            END_LISTS();
            return 0;
        }
        SLOT(SrObject, primary) = 0;
        { SrObject *a_ = primary; ADD(a_); }
        SLOT(SrObject, second) = 0;
        { SrObject *a_ = second; ADD(a_); }
        SLOT(SrObject, third) = 0;
        { SrObject *a_ = third; ADD(a_); }
        SLOT(SrObject, found) = 0;
        { SrObject *a_ = found; ADD(a_); }
        FETCH(t160, DAT_004e4778, DAT_0055f460[0]);
        held = SLOT(SrObject, found);
        if (held != 0) {
            SET_REF(primary, asMaterial(held));
            FUN_001cade0(self, info, primary, shared, keys, values);
            FETCH(t156, DAT_004e4788, DAT_0055f460[0]);
            held = SLOT(SrObject, found);
            if (held == 0) {
                END_REFS();
                END_LISTS();
                return 0;
            }
            SET_REF(second, asMaterial(held));
            FUN_001cade0(self, info, second, shared, keys, values);
        } else {
            FETCH(t152, DAT_004e4658, DAT_0055f460[0]);
            held = SLOT(SrObject, found);
            if (held == 0) {
                END_REFS();
                END_LISTS();
                return 0;
            }
            SET_REF(primary, asMaterial(held));
            SET_REF(second, primary);
            FUN_001cade0(self, info, primary, shared, keys, values);
        }
        FETCH(t148, DAT_004e4798, DAT_00561830[0]);
        held = SLOT(SrObject, found);
        if (held != 0) {
            SET_REF(third, asTexture(held));
            FUN_001cade0(self, info, third, shared, keys, values);
        }
        FUN_001d86f0(passes, i, primary);
        FUN_001d87b0(passes, i, second);
        FUN_001d8870(passes, i, third);
        END_REFS();
    }
    END_LISTS();
    return 1;
}
