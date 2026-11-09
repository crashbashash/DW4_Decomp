#include "dw4/igSmartPointer.h"
extern "C" {
igObject *FUN_002b9500(int);
int FUN_0030b7e0(igObject *, int *, int, int);
int igObject_GetAllocator(igFolder *);
extern int DAT_004f9a78[4];
}

extern "C" igSmartPointer<igObject> Gap__Core__igFolder__vfunc_23(igFolder *folder, int name) {
    igSmartPointer<igObject> item(FUN_002b9500(igObject_GetAllocator(folder)));
    FUN_0030b7e0(item.get(), &DAT_004f9a78[0], folder->_folderName, name);
    return item;
}
