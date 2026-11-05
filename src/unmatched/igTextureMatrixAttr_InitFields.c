struct V { int x; int y; int z; int w; };
struct M { int m[16]; };
struct Fld { char pad[48]; int f48; };
int FUN_00130e90();
int FUN_0018c640();
int FUN_0030a520(void *, int);
int igMetaObject_CreateFields();
struct Fld *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
void FUN_00141520(void);  /* code at 0x141520, passed by address (was DAT_141520; docs/engine/function-inventory.md) */
extern int DAT_00485b20[4];
extern int DAT_00485b30[4];
extern int DAT_00485b40[4];
extern int DAT_00485b50[4];
extern int DAT_0055ecd8[4];

void igTextureMatrixAttr_InitFields(void) {
    void *temp_s0;
    struct V o5;
    struct V o4;
    void *temp_s1;
    struct Fld *fld;
    struct V o3;
    struct V o2;
    int temp_s2;
    struct M o1;

    temp_s0 = (void *)DAT_0055ecd8[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00485b20[0], 4);
    temp_s1 = igMetaObject_GetFieldAt(temp_s0, temp_s2);
    o5.x = 0;
    o5.y = 0;
    o5.z = 0;
    o5.w = 0x3F800000;
    o4.x = 0;
    o4.y = 0;
    o4.z = 0x3F800000;
    o4.w = 0;
    o3.x = 0;
    o3.y = 0x3F800000;
    o3.z = 0;
    o3.w = 0;
    o2.x = 0x3F800000;
    o2.y = 0;
    o2.z = 0;
    o2.w = 0;
    FUN_00130e90(&o1, &o2, &o3, &o4, &o5);
    FUN_0018c640(temp_s1, &o1);
    fld = igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1);
    fld->f48 = (int)FUN_00141520;
    FUN_0030a520(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2), -1);
    igMetaObject_NameFields(temp_s0, &DAT_00485b30[0], &DAT_00485b40[0], &DAT_00485b50[0], temp_s2);
}
