#include "dw4/reflected.h"
int igObject_InitHeader(void *);
int FUN_0033ec00();
int ObjectRef_Destruct_00150eb0();
int StringRef_Destruct_00130720();
extern int DAT_00536f10[4];
extern void * DAT_00586dc8[4];
int beMessengerWork_GetVTable(void) {
    beMessengerWork obj;
    int t;
    igObject_InitHeader(&obj);
    obj._vtable = (int)&DAT_00536f10[0];
    obj._groupName = 0;
    obj._infoName = 0;
    obj._message = 0;
    obj._findRamNoList = 0;
    obj._findRamList = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj._vtable = (int)&DAT_00536f10[0];
    FUN_0033ec00(&obj._findRamList, -1);
    ObjectRef_Destruct_00150eb0(&obj._findRamNoList, -1);
    StringRef_Destruct_00130720(&obj._message, -1);
    StringRef_Destruct_00130720(&obj._infoName, -1);
    StringRef_Destruct_00130720(&obj._groupName, -1);
    return t;
}
