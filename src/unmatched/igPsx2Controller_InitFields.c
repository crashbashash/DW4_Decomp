int FUN_00145d40();
int FUN_002d3890();
int FUN_002dc7a0();
int FUN_002ea4b0();
int FUN_0030eda0();
int igMetaObject_CreateFields();
struct Fld { char p0[52]; int f52; int f56; };
struct Fld *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_004875d0[4];
extern int DAT_00487630[4];
extern int DAT_00487690[4];
extern int DAT_004876f0[4];
extern int DAT_00487750[4];
extern int DAT_00487758[4];
extern int DAT_0055f760[4];
int FUN_00147030();
int FUN_002d1870();

void igPsx2Controller_InitFields(void) {
    int temp_s1;
    void *temp_s2;
    void *temp_v0;
    void *temp_v0_2;
    void *temp_s0;

    temp_s0 = (void *)DAT_0055f760[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004875d0[0], 0x18);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 3), 0x10);
    FUN_0030eda0(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 4), 2);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 5));
    *(int *)((char *)(temp_s2) + 56) = FUN_00145d40();
    { struct Fld *q = igMetaObject_GetFieldAt(temp_s0, temp_s1 + 6); q->f52 = 2; }
    { struct Fld *q = igMetaObject_GetFieldAt(temp_s0, temp_s1 + 7); q->f52 = 2; }
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 9));
    FUN_002dc7a0(temp_v0, &DAT_00487750[0]);
    *(int *)((char *)(temp_v0) + 52) = (int)(&FUN_002d1870);
    FUN_0030eda0(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xC), 0xFFFF);
    { struct Fld *q = igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xE); q->f52 = 2; }
    { struct Fld *q = igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xF); q->f52 = 2; }
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x10), 1);
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x11), 1);
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x12), 1);
    temp_v0_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x14));
    FUN_002dc7a0(temp_v0_2, &DAT_00487758[0]);
    *(int *)((char *)(temp_v0_2) + 52) = (int)(&FUN_00147030);
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x15), 1);
    igMetaObject_NameFields(temp_s0, &DAT_00487630[0], &DAT_00487690[0], &DAT_004876f0[0], temp_s1);
}
