#include "dw4/reflected.h"
extern "C" {
void igObject_Destroy(igObject *);
int FUN_002eb010(...);
void *StringPool_Construct(...);
char *StringPool_Intern(...);
int StringChunk_ReleaseHeader(...);
extern int DAT_004f6518[4];
extern void *DAT_00586f20[4];
}
struct Rel { static inline void go(igObject *object) {
    if (object) {
        --object->_refCount;
        if (((unsigned long long)(long long)object->_refCount & 0x7fffffULL) == 0)
            igObject_Destroy(object);
    }
} };
/* matching construct: string-pool header lives at s-8 (chunk) / s-4 (refcount); not a reflected class */
struct SRel { static inline void go(char *s) {
    if (s) {
        int *a1 = (int *)(s - 8);
        int v = *(int *)(s - 4) - 1;
        *(int *)(s - 4) = v;
        if (v == 0) {
            StringChunk_ReleaseHeader(*a1, a1);
        }
    }
} };
struct Pool { static inline void *get() {
    if (DAT_00586f20[0] == 0) {
        void *p = (void *)FUN_002eb010(16);
        if (p != 0) {
            p = StringPool_Construct(p);
        }
        DAT_00586f20[0] = p;
    }
    return DAT_00586f20[0];
} };
extern "C" void FUN_00301590(igObjectDirEntry *arg0, igMetaObject *arg1);
void FUN_00301590(igObjectDirEntry *arg0, igMetaObject *arg1) {
    char *s0;
    if (arg1) {
        arg1->_refCount++;
    }
    /* matching construct: _typeMeta/_typeMetaName are 4-byte reference fields (int); cast to the typed pointer */
    Rel::go((igObject *)arg0->_typeMeta);
    arg0->_typeMeta = (int)arg1;
    if (arg1) {
        char *name = (char *)arg1->_name;
        void *pool = Pool::get();
        s0 = StringPool_Intern(pool, name);
        SRel::go((char *)arg0->_typeMetaName);
        arg0->_typeMetaName = (int)s0;
    } else {
        void *pool = Pool::get();
        s0 = StringPool_Intern(pool, DAT_004f6518);
        SRel::go((char *)arg0->_typeMetaName);
        arg0->_typeMetaName = (int)s0;
    }
}
