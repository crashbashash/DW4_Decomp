class IniTarget {
public:
    virtual void d0();    virtual void d1();    virtual void d2();    virtual void d3();    virtual void d4();    virtual void d5();    virtual void d6();    virtual void d7();    virtual void d8();    virtual void d9();    virtual void d10();    virtual void d11();    virtual void d12();    virtual void d13();    virtual void d14();    virtual void d15();    virtual void d16();    virtual void d17();    virtual void d18();    virtual void d19();
    virtual void *getMeta();
};
struct IniItemList { char pad0[8]; int count; char pad1[4]; void **data; };
struct IniFieldView { char pad0[56]; void *refMeta; };
extern "C" {
void StringList_CopyRetained(char **, void *, int);
void StringChunk_ReleaseHeader(int, int *);
IniFieldView *igMetaObject_FindFieldByName(void *, char *);
int igObject_IsKindOf(void *, void *);
void igObjectRefMetaField_Assign(IniFieldView *, IniTarget *, void *);
extern void *DAT_00585b20[4];
}
struct IniStrRef {
    char *p;
    IniStrRef() {}
    IniStrRef(const IniStrRef &o) : p(o.p) { if (p != 0) ((int *)p)[-1] = ((int *)p)[-1] + 1; }
    static inline void Release(char *s) {
        int *x = (int *)s;
        if (x != 0) { int *hd = x - 2; int c = x[-1] - 1; x[-1] = c; if (c == 0) StringChunk_ReleaseHeader(*hd, hd); }
    }
    ~IniStrRef() { Release(p); }
};
static inline IniFieldView *asObjectRefField(IniFieldView *f) {
    if (f != 0 && igObject_IsKindOf(f, DAT_00585b20[0]) != 0) {
        return f;
    }
    return 0;
}
extern "C" int FUN_001cafc0(void *, IniStrRef, int);
static inline void *itemAt(IniItemList *l, int i) { return l->data[i]; }
extern "C" void FUN_001cade0(void *self, IniTarget *target, IniItemList *items, void *names, void *lookup, void *fieldNames) {
    int i;
    for (i = 0; i < items->count; i++) {
        void *item = itemAt(items, i);
        IniStrRef name;
        int index;
        StringList_CopyRetained(&name.p, names, i);
        index = FUN_001cafc0(lookup, name, 0);
        if (index != -1) {
            IniStrRef fieldName;
            IniFieldView *field;
            StringList_CopyRetained(&fieldName.p, fieldNames, index);
            field = asObjectRefField(igMetaObject_FindFieldByName(target->getMeta(), fieldName.p));
            if (field != 0 && igObject_IsKindOf(item, field->refMeta) != 0) {
                igObjectRefMetaField_Assign(field, target, item);
            }
        }
    }
}
