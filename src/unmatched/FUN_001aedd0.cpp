#include "dw4/reflected.h"
struct AnimDbRecordView { int _vtable; unsigned int _refCount; int _name; };
struct AnimDbList { char pad[8]; int _count; int _capacity; AnimDbRecordView **_data; };
extern igMetaObject *DAT_00585bd8;
extern char DAT_004e0858[];
extern "C" {
int igObject_IsKindOf(AnimDbRecordView *, igMetaObject *);
int igObject_Destroy(AnimDbRecordView *);
int FUN_002e2d30(int, void *, const char *, AnimDbRecordView *);
int FUN_001aedd0(void *self, AnimDbList *list, int file, AnimDbRecordView *obj);
}
struct AnimDbRef {
    AnimDbRecordView *volatile p;
    inline void set(AnimDbRecordView *o) { p = o; AnimDbRecordView *q = p; if (q != 0) q->_refCount = q->_refCount + 1; }
    inline void release() {
        AnimDbRecordView *q = p;
        if (q != 0) {
            q->_refCount = q->_refCount - 1;
            if (((unsigned long long)((long long)(int)q->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q);
            }
        }
    }
};
static inline AnimDbRecordView *castToNamed(AnimDbRecordView *o) {
    if (o != 0 && igObject_IsKindOf(o, DAT_00585bd8) != 0) {
        return o;
    }
    return 0;
}
static inline const char *nameOf(AnimDbRecordView *o) {
    const char *n = (const char *)o->_name;
    if (n != 0) {
        return n;
    }
    return DAT_004e0858;
}
static inline int indexOf(AnimDbList *list, AnimDbRecordView *const volatile &key) {
    int n = list->_count;
    AnimDbRecordView *k = key;
    int i;
    for (i = 0; i < n; i++) {
        if (k == list->_data[i]) {
            return i;
        }
    }
    return -1;
}
int FUN_001aedd0(void *self, AnimDbList *list, int file, AnimDbRecordView *obj) {
    AnimDbRef held;
    AnimDbRef named;
    AnimDbRecordView *volatile key;
    AnimDbRecordView *o;
    held.set(obj);
    o = held.p;
    key = o;
    if (indexOf(list, key) != -1) {
        named.set(castToNamed(o));
        AnimDbRecordView *got = named.p;
        if (got != 0) {
            const char *name = nameOf(got);
            int result;
            result = (unsigned char)FUN_002e2d30(file, self, name, obj);
            named.release();
            held.release();
            return result;
        }
        if (got != 0) {
            got->_refCount = got->_refCount - 1;
            if (((unsigned long long)((long long)(int)got->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(got);
            }
        }
    }
    held.release();
    return 0;
}
