typedef struct MetaEnumNameList { char pad[4]; int _refCount; int count; int capacity; char **data; } MetaEnumNameList;
typedef struct MetaEnumValueList { char pad[4]; int _refCount; int count; int capacity; int *data; } MetaEnumValueList;
typedef struct MetaEnumView { char pad[4]; int _refCount; char *name; MetaEnumNameList *names; MetaEnumValueList *values; } MetaEnumView;
MetaEnumNameList *FUN_002b90e0(int);
MetaEnumView *FUN_002befe0(int);
MetaEnumValueList *FUN_002caa70(int);
void FUN_002d30b0(int, MetaEnumView *);
int FUN_002eb010(int);
void List_Resize(MetaEnumValueList *, int, int);
int Memory_GetAllocatorBySelector(int);
void StringChunk_ReleaseHeader(int, int *);
void StringList_Resize(MetaEnumNameList *, int);
int StringPool_Construct(int);
char *StringPool_Intern(int, char *);
void igObject_Destroy(void *);
extern int DAT_00586dc8;
extern int DAT_00586f20;
extern int DAT_00587040;
static inline int pool(void) {
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
static inline void dropNames(MetaEnumNameList *o) {
    if (o != 0) {
        o->_refCount = o->_refCount - 1;
        if (((unsigned long long)((long long)o->_refCount << 0x29) >> 0x29) == 0) { igObject_Destroy(o); }
    }
}
static inline void dropValues(MetaEnumValueList *o) {
    if (o != 0) {
        o->_refCount = o->_refCount - 1;
        if (((unsigned long long)((long long)o->_refCount << 0x29) >> 0x29) == 0) { igObject_Destroy(o); }
    }
}
static inline void setValue(MetaEnumValueList *l, int i, int *v) { if (l->count != 0 && i >= 0 && i < l->count) { l->data[i] = *v; } }
MetaEnumView *igMetaEnum_Create(char *name, char **names, int *values, int count) {
    MetaEnumView *e;
    int i;
    char *v;
    char *entry;
    char *held;
    char *old;
    MetaEnumNameList *nl;
    MetaEnumValueList *vl;
    int a;
    char **slot;
    e = FUN_002befe0(Memory_GetAllocatorBySelector(DAT_00587040));
    v = StringPool_Intern(pool(), name);
    old = e->name;
    dropString(old);
    e->name = v;
    a = Memory_GetAllocatorBySelector(DAT_00587040);
    dropNames(e->names);
    e->names = FUN_002b90e0(a);
    StringList_Resize(e->names, count);
    a = Memory_GetAllocatorBySelector(DAT_00587040);
    dropValues(e->values);
    e->values = FUN_002caa70(a);
    vl = e->values;
    if (count >= 0) {
        if (!(count > vl->capacity)) {
            vl->count = count;
        } else {
            List_Resize(vl, count, 4);
        }
    }
    for (i = 0; i < count; i++) {
        entry = names[i];
        if (entry == 0) {
            v = 0;
        } else {
            v = StringPool_Intern(pool(), entry);
        }
        *(char **)&held = v;
        nl = e->names;
        if (nl->count != 0 && i >= 0 && i < nl->count) {
            slot = &nl->data[i];
            if (held != 0) { ((int *)held)[-1] = ((int *)held)[-1] + 1; }
            old = *slot;
            dropString(old);
            *slot = held;
        }
        dropString(held);
        setValue(e->values, i, &values[i]);
    }
    FUN_002d30b0(DAT_00586dc8, e);
    e->_refCount = e->_refCount - 1;
    if (((unsigned long long)((long long)e->_refCount << 0x29) >> 0x29) == 0) { igObject_Destroy(e); }
    return e;
}
