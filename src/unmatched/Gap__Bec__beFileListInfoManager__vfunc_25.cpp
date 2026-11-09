#include "dw4/reflected.h"
extern "C" {
void *FUN_00236f80(int, int);
void FUN_00382df0(void *, igObject *);
void List_InsertWords(void *, int, int, void *);
void ObjectList_AppendRetained(igObjectList *, igObject *);
extern int DAT_00585bc0[4];
extern int DAT_00589678[4];
extern int DAT_00589760[4];
int Gap__Bec__beFileListInfoManager__vfunc_25(beFileListInfoManager *self, igObject *info);
}
class MetaVt { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int getMeta(); };


static inline void insertWords(igObjectList *l, int at, int n, igObject **src) {
    int i;
    for (i = 0; i < n; i++) {
        igObject *v = src[i];
        if (v) ++v->_refCount;
    }
    List_InsertWords(l, at, n, (void *)src);
}

int Gap__Bec__beFileListInfoManager__vfunc_25(beFileListInfoManager *self, igObject *info) {
    if (DAT_00589760[0] == ((MetaVt *)info)->getMeta()) {
        igObjectList *list = (igObjectList *)self->_infoList;
        if (list->_count > 0) {
            igObject *first = info;
            insertWords(list, 0, 1, &first);
        } else {
            ObjectList_AppendRetained(list, info);
        }
        self->_proc = 0;
        ((beSystem *)self->_system)->_isSResetEnable = 0;
        return 1;
    }
    if (DAT_00585bc0[0] == ((MetaVt *)info)->getMeta()) {
        void *found = FUN_00236f80(self->_insight, DAT_00589678[0]);
        if (found == 0) return 0;
        FUN_00382df0(found, info);
        return 1;
    }
    return 0;
}
