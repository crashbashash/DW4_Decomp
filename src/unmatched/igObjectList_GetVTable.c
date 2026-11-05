#include "dw4/reflected.h"
int igObject_InitHeader(igObjectList *);
extern int DAT_005249b0[4];
extern void * DAT_00586dc8[4];
int igObjectList_GetVTable(void) {
    igObjectList obj;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&DAT_005249b0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}
