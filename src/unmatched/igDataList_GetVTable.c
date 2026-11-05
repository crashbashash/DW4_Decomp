#include "dw4/reflected.h"
/* matching construct: stack object padded to retail's 32-byte frame slot (igObject header + scratch) */
struct ObjFrame { igObject head; char pad[24]; };
int igObject_InitHeader(igObject *);
extern int DAT_005309b0[4];
extern void * DAT_00586dc8[4];
int igDataList_GetVTable(void) {
    struct ObjFrame obj;

    igObject_InitHeader(&obj.head);
    obj.head._vtable = (int)&DAT_005309b0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}
