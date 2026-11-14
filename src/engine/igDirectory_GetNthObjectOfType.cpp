#include "dw4/igSmartPointer.h"

extern "C" {
int igDirectory_GetInfo(igObject *, unsigned int);
unsigned int igDirectory_GetInfoCount(igObject *);
int igObject_IsKindOf(int, igObject *);
igSmartPointer<igObject> igResource_GetDirectory(int, int);
igObject *igObjectSystem_FindMetaByNameDefault(int);
int igDirectory_GetNthObjectOfType(int directory, int name, int metaName, int wanted) {
    igSmartPointer<igObject> list = igResource_GetDirectory(directory, name);
    igSmartPointer<igObject> meta(igObjectSystem_FindMetaByNameDefault(metaName), kRetainReference);
    int found;
    unsigned int i;
    if (list.get() == 0 || meta.get() == 0) {
        return 0;
    }
    found = 0;
    for (i = 0; i < igDirectory_GetInfoCount(list.get()); i++) {
        if (igObject_IsKindOf(igDirectory_GetInfo(list.get(), i), meta.get()) != 0) {
            if (found++ == wanted) {
                return igDirectory_GetInfo(list.get(), i);
            }
        }
    }
    return 0;
}
}
