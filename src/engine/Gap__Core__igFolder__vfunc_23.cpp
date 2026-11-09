#include "dw4/reflected.h"
extern "C" {
igObject *FUN_002b9500(int);
int FUN_0030b7e0(igObject *, int *, int, int);
int igObject_GetAllocator(igFolder *);
int igObject_Destroy(igObject *);
extern int DAT_004f9a78[4];
}
struct FolderItemRef {
    igObject *p;
    FolderItemRef(igObject *object) : p(object) {}
    FolderItemRef(const FolderItemRef &other) : p(other.p) {
        if (p != 0) p->_refCount = p->_refCount + 1;
    }
    ~FolderItemRef() {
        igObject *object = p;
        if (object != 0) {
            object->_refCount = object->_refCount - 1;
            if ((object->_refCount & 0x7FFFFF) == 0) igObject_Destroy(object);
        }
    }
    igObject *get() const { return p; }
};
extern "C" FolderItemRef Gap__Core__igFolder__vfunc_23(igFolder *folder, int name) {
    FolderItemRef item(FUN_002b9500(igObject_GetAllocator(folder)));
    FUN_0030b7e0(item.get(), &DAT_004f9a78[0], folder->_folderName, name);
    return item;
}
