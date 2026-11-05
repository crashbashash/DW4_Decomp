/* 0x0019cfb0 — igNode_InitFields. Banked by tools/retype_struct_member.py (shape: width):
 * the m2c draft plus a mechanical source respelling, verified
 * byte-identical to retail by tools/verify.py. */
#include "dw4/reflected.h"
int FUN_00186a80();
int FUN_0019c8c0();
int FUN_002ea4b0();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_0048bc90[4];
extern int DAT_0048bca0[4];
extern int DAT_0048bcb0[4];
extern int DAT_0048bcc0[4];
extern int DAT_00561838[4];
void igNode_InitFields(void) {
    int temp_s0;
    void *temp_s1;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_v0;

    temp_s1 = (void *)DAT_00561838[0];
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_0048bc90[0], 4);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = FUN_00186a80();
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = FUN_0019c8c0();
    ((igObjectRefMetaField *)temp_s2_2)->_resetMethod = 3;
    ((igObjectRefMetaField *)temp_s2_2)->_construct = 1;
    ((igObjectRefMetaField *)temp_s2_2)->_persistent = 0;
    ((igObjectRefMetaField *)temp_s2_2)->_deepCopyMethod = 4;
    ((igObjectRefMetaField *)temp_s2_2)->_shallowCopyMethod = 4;
    ((igObjectRefMetaField *)temp_s2_2)->_constructCopyMethod = 4;
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3));
    FUN_002ea4b0(temp_v0, -1);
    ((igIntMetaField *)temp_v0)->_persistent = 0;
    igMetaObject_NameFields(temp_s1, &DAT_0048bca0[0], &DAT_0048bcb0[0], &DAT_0048bcc0[0], temp_s0);
}
