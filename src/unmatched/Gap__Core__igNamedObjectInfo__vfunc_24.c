#include "dw4/reflected.h"
int igObject_GetFieldValueByName();
int strcmp();
extern int DAT_004e0858[4];
int Gap__Core__igNamedObjectInfo__vfunc_24(igNamedObjectInfo *arg0, int arg1) {
    int i;
    int off;
    int *name;
    if (arg1 == 0) {
        return 0;
    }
    for (i = 0; i < ((igObjectList *)arg0->_objects)->_count; i++) {
        off = i * 4;
        name = (int *)&((igNamedObject *)((int *)((igObjectList *)arg0->_objects)->_data)[i])->_name;
        name = *(int **)name;
        if (name != 0) {
            name = (int *)name;
        } else {
            name = (int *)&DAT_004e0858[0];
        }
        if (strcmp(name, arg1) == 0) {
            return ((int *)((igObjectList *)arg0->_objects)->_data)[i];
        }
    }
    return igObject_GetFieldValueByName(arg0, arg1);
}
