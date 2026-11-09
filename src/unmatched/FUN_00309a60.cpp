#include "dw4/igSmartPointer.h"

extern "C" {
int FUN_002d8370(igObject *, unsigned int);
unsigned int FUN_002d9120(igObject *);
int igObject_IsKindOf(int, igObject *);
igSmartPointer<igObject> FUN_003087a0(int, int);
igObject *igObjectSystem_FindMetaByNameDefault(int);
int FUN_00309a60(int directory, int name, int metaName, int wanted) {
    igSmartPointer<igObject> list = FUN_003087a0(directory, name);
    igSmartPointer<igObject> meta(igObjectSystem_FindMetaByNameDefault(metaName), kRetainReference);
    int found;
    unsigned int i;
    if (list.get() == 0 || meta.get() == 0) {
        return 0;
    }
    found = 0;
    for (i = 0; i < FUN_002d9120(list.get()); i++) {
        if (igObject_IsKindOf(FUN_002d8370(list.get(), i), meta.get()) != 0) {
            if (found++ == wanted) {
                return FUN_002d8370(list.get(), i);
            }
        }
    }
    return 0;
}
}
