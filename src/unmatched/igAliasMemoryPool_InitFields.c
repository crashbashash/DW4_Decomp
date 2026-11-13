int FUN_002ba690();
int igMemoryPool_GetOrCreateMetaObject();
int FUN_002c57c0();
int FUN_002ea4b0();
int FUN_0030ec10();
int FUN_0030eda0();
int igMetaObject_CreateFields();
struct Fld *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
extern int DAT_004c15b0[4];
extern int DAT_004c15f0[4];
extern int DAT_004c1630[4];
extern int DAT_004c1670[4];
extern void * DAT_005869b0[4];
int thunk_igMemoryPool_GetMetaObject();

struct Fld { char p0[52]; char f52; char f53; char p54[2]; int f56; };
void igAliasMemoryPool_InitFields(void) {
    struct Fld *temp_s1;
    struct Fld *temp_s1_2;
    int temp_s2;
    struct Fld *temp_s1_3;
    void *temp_s0;

    temp_s0 = (void *)(DAT_005869b0[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c15b0[0], 0xE);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s2), -1);
    FUN_0030ec10(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 4), 0xFFFFFFFFFFFFFFFFULL);
    temp_s1 = igMetaObject_GetFieldAt(temp_s0, temp_s2 + 5);
    temp_s1->f56 = FUN_002c57c0();
    temp_s1_2 = igMetaObject_GetFieldAt(temp_s0, temp_s2 + 0xA);
    temp_s1_2->f56 = FUN_002ba690();
    FUN_0030eda0(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 0xC), 8);
    temp_s1_3 = igMetaObject_GetFieldAt(temp_s0, temp_s2 + 0xD);
    temp_s1_3->f56 = igMemoryPool_GetOrCreateMetaObject();
    temp_s1_3->f52 = 0;
    temp_s1_3->f53 = 0;
    igMetaObject_NameFields(temp_s0, &DAT_004c15f0[0], &DAT_004c1630[0], &DAT_004c1670[0], temp_s2);
    *(int *)((char *)(DAT_005869b0[0]) + 64) = (int)(&thunk_igMemoryPool_GetMetaObject);
}
