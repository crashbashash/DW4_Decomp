int FUN_002ca030();
int FUN_002dc7a0();
int FUN_002ea4b0();
int FUN_0030e750();
int FUN_0030ec10();
int igMetaObject_CreateFields();
struct Fld *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_0048c4e0[4];
extern int DAT_0048c510[4];
extern int DAT_0048c540[4];
extern int DAT_0048c570[4];
extern int DAT_0048c5a0[4];
extern int DAT_00561c38[4];
int FUN_002d1870();

struct Fld { char p0[38]; char f38; char p39[13]; int f52; int f56; };
void igCompressedAnimationSequenceQS_InitFields(void) {
    int temp_s0;
    int temp_s1;
    struct Fld *temp_s2;
    struct Fld *temp_s2_2;
    struct Fld *temp_s2_3;
    struct Fld *temp_s2_4;
    struct Fld *temp_v0;
    struct Fld *temp_v0_2;

    temp_s1 = DAT_00561c38[0];
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_0048c4e0[0], 0xC);
    temp_s2 = igMetaObject_GetFieldAt(temp_s1, temp_s0);
    temp_s2->f56 = FUN_002ca030();
    temp_s2_2 = igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1);
    temp_s2_2->f56 = FUN_002ca030();
    temp_s2_3 = igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2);
    temp_s2_3->f56 = FUN_002ca030();
    FUN_0030ec10(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 7), 0xFFFFFFFFFFFFFFFFULL);
    temp_v0 = igMetaObject_GetFieldAt(temp_s1, temp_s0 + 8);
    FUN_002dc7a0(temp_v0, &DAT_0048c5a0[0]);
    temp_v0->f52 = (int)&FUN_002d1870;
    temp_v0_2 = igMetaObject_GetFieldAt(temp_s1, temp_s0 + 9);
    FUN_002ea4b0(temp_v0_2, 1);
    temp_v0_2->f38 = 0;
    FUN_0030e750(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xA), 0);
    temp_s2_4 = igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xB);
    temp_s2_4->f52 = 3;
    igMetaObject_NameFields(temp_s1, &DAT_0048c510[0], &DAT_0048c540[0], &DAT_0048c570[0], temp_s0);
}
