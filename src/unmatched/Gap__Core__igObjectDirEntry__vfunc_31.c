#include "dw4/reflected.h"
typedef struct DirEntryCounted { char pad[4]; int _refCount; } DirEntryCounted;
typedef struct DirEntryMetaList { char pad[16]; DirEntryCounted **data; } DirEntryMetaList;
typedef struct DirEntryFileView { char pad[192]; DirEntryMetaList *metas; char pad2[80]; char failed; char pad3[11]; int pool; } DirEntryFileView;
typedef struct DirEntrySelf { char pad[12]; int index; char pad2[12]; DirEntryCounted *typeMeta; int typeMetaName; char pad3[8]; int pool; int typeMetaIndex; } DirEntrySelf;
int FUN_002d7da0(DirEntryFileView *, int, DirEntryCounted *);
int Memory_GetAllocatorBySelector(int);
DirEntryCounted *igMetaObject_CreateInstanceWithPool(DirEntryCounted *, int);
DirEntryCounted *igObjectSystem_FindMetaByNameDefault(int);
int igObject_Destroy(void *);
static inline void addRef(DirEntryCounted *o) { if (o != 0) { o->_refCount = o->_refCount + 1; } }
static inline void dropRef(DirEntryCounted *o) {
    o->_refCount = o->_refCount - 1;
    if (((unsigned long long)((long long)o->_refCount << 0x29) >> 0x29) == 0) { igObject_Destroy(o); }
}
static inline void setMeta(DirEntrySelf *self, DirEntryCounted *m) {
    DirEntryCounted *old;
    addRef(m);
    old = self->typeMeta;
    if (old != 0) { dropRef(old); }
    self->typeMeta = m;
}
void Gap__Core__igObjectDirEntry__vfunc_31(DirEntrySelf *self, DirEntryFileView *file) {
    int index;
    DirEntryCounted *m;
    DirEntryCounted *obj;
    int pool;
    int sel;
    index = self->typeMetaIndex;
    if (index == -1) {
        setMeta(self, igObjectSystem_FindMetaByNameDefault(self->typeMetaName));
    } else {
        setMeta(self, file->metas->data[index]);
    }
    if (self->typeMeta != 0) {
        sel = self->pool;
        if (sel == -1 || sel == 1 || sel == 2) {
            pool = file->pool;
        } else {
            pool = Memory_GetAllocatorBySelector(sel);
            if (pool == 0) {
                pool = file->pool;
            }
        }
        obj = igMetaObject_CreateInstanceWithPool(self->typeMeta, pool);
        if (obj == 0) {
            file->failed = 1;
            FUN_002d7da0(file, self->index, 0);
            return;
        }
        FUN_002d7da0(file, self->index, obj);
        dropRef(obj);
    } else {
        FUN_002d7da0(file, self->index, 0);
    }
}
