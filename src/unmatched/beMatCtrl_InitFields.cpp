struct F { char pad[52]; int f52; int f56; char f60; };
extern "C" {
int FUN_0035b770(void);
int igIntList_GetOrCreateMetaObject(void);
int igMetaObject_CreateFields(int, int *, int);
struct F *igMetaObject_GetFieldAt(int, int);
int igMetaObject_GetFieldCount(int);
int igMetaObject_NameFields(int, int *, int *, int *, int);
extern int DAT_004c6180[4];
extern int DAT_004c61b0[4];
extern int DAT_004c61e0[4];
extern int DAT_004c6210[4];
extern int DAT_00589160[4];
void beMatCtrl_InitFields(void);
}
void beMatCtrl_InitFields(void) {
    int temp_s0;
    int temp_s2;
    struct F *temp_s1;
    struct F *temp_s1_2;
    struct F *temp_s1_3;
    struct F *t;

    temp_s0 = DAT_00589160[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c6180[0], 9);
    t = igMetaObject_GetFieldAt(temp_s0, temp_s2 + 4);
    t->f52 = 4;
    temp_s1 = igMetaObject_GetFieldAt(temp_s0, temp_s2 + 5);
    temp_s1->f56 = igIntList_GetOrCreateMetaObject();
    temp_s1_2 = igMetaObject_GetFieldAt(temp_s0, temp_s2 + 6);
    temp_s1_2->f56 = igIntList_GetOrCreateMetaObject();
    temp_s1_3 = igMetaObject_GetFieldAt(temp_s0, temp_s2 + 8);
    temp_s1_3->f56 = FUN_0035b770();
    temp_s1_3->f60 = 0;
    igMetaObject_NameFields(temp_s0, &DAT_004c61b0[0], &DAT_004c61e0[0], &DAT_004c6210[0], temp_s2);
}
