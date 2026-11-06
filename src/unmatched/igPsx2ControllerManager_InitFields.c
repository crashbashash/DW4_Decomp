#include "dw4/reflected.h"
int FUN_002d3890();
int FUN_002dc7a0();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_00487530[4];
extern int DAT_00487540[4];
extern int DAT_00487550[4];
extern int DAT_00487560[4];
extern int DAT_00487570[4];
extern int DAT_0055f738[4];
int FUN_00146d90();

void igPsx2ControllerManager_InitFields(void) {
    void *temp_s0;
    void *temp_v0;
    int temp_s2;

    temp_s0 = (void *)DAT_0055f738[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00487530[0], 3);
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    FUN_002dc7a0(temp_v0, &DAT_00487570[0]);
    ((igEnumMetaField *)temp_v0)->_getMetaEnumFunction = (int)(&FUN_00146d90);
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2), 1);
    igMetaObject_NameFields(temp_s0, &DAT_00487540[0], &DAT_00487550[0], &DAT_00487560[0], temp_s2);
}
