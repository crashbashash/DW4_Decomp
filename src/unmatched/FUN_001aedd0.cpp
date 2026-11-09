#include "dw4/reflected.h"
struct AnimDbRecord { int vtable; unsigned int references; const char *name; };
extern igMetaObject *DAT_00585bd8;
extern char DAT_004e0858[];
extern "C" {
int igObject_IsKindOf(AnimDbRecord *, igMetaObject *);
int igObject_Destroy(AnimDbRecord *);
int FUN_002e2d30(int, void *, const char *, AnimDbRecord *);
}
struct RecordRef {
    AnimDbRecord *p;
    RecordRef(AnimDbRecord *object) : p(object) {
        if (p != 0) {
            p->references = p->references + 1;
        }
    }
    ~RecordRef() {
        AnimDbRecord *object = p;
        if (object != 0) {
            object->references = object->references - 1;
            if ((object->references & 0x7FFFFF) == 0) {
                igObject_Destroy(object);
            }
        }
    }
};
static inline AnimDbRecord *castToNamed(AnimDbRecord *object) {
    if (object != 0 && igObject_IsKindOf(object, DAT_00585bd8) != 0) {
        return object;
    }
    return 0;
}
static inline const char *nameOf(AnimDbRecord *object) {
    const char *name = object->name;
    if (name != 0) {
        return name;
    }
    return DAT_004e0858;
}
#include "dw4/igTDataList.h"
extern "C" int FUN_001aedd0(void *self, igTDataList<AnimDbRecord *> *list, int file, AnimDbRecord *object) {
    RecordRef held(object);
    AnimDbRecord *current = held.p;
    if (list->find(current) != -1) {
        RecordRef named(castToNamed(current));
        if (named.p != 0) {
            return (unsigned char)FUN_002e2d30(file, self, nameOf(named.p), object);
        }
    }
    return 0;
}
