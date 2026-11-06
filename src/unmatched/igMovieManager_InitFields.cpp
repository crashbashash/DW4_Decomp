/* C++ translation unit: the unit compiled with exceptions on and retail keeps this function's
 * exception index record, which only the C++ front end emits. */
struct Fld { char p0[38]; char f38; char p1[13]; char f52; int f56; };
extern "C" {
int FUN_00142f70(void);
int FUN_00335440(void);
int FUN_00335de0(void);
int FUN_00336860(void);
int FUN_0044c4d0(void);
int igMetaObject_CreateFields(void *, int *, int);
struct Fld *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c2bb0[4];
extern int DAT_004c2bd0[4];
extern int DAT_004c2bf0[4];
extern int DAT_004c2c10[4];
extern int DAT_00587870[4];
void igMovieManager_InitFields(void);
}
void igMovieManager_InitFields(void) {
    struct Fld *temp_s2;
    struct Fld *temp_s2_2;
    struct Fld *temp_s2_3;
    struct Fld *temp_s2_4;
    struct Fld *temp_s2_5;
    void *temp_s1;
    int temp_s0;

    temp_s1 = (void *)DAT_00587870[0];
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_004c2bb0[0], 6);
    temp_s2 = igMetaObject_GetFieldAt(temp_s1, temp_s0);
    temp_s2->f56 = FUN_00335de0();
    igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1)->f38 = 0;
    temp_s2_2 = igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2);
    temp_s2_2->f56 = FUN_00142f70();
    temp_s2_2->f38 = 0;
    temp_s2_3 = igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3);
    temp_s2_3->f56 = FUN_00335440();
    temp_s2_3->f38 = 0;
    temp_s2_4 = igMetaObject_GetFieldAt(temp_s1, temp_s0 + 4);
    temp_s2_4->f56 = FUN_00336860();
    temp_s2_4->f52 = 1;
    temp_s2_4->f38 = 0;
    temp_s2_5 = igMetaObject_GetFieldAt(temp_s1, temp_s0 + 5);
    temp_s2_5->f56 = FUN_0044c4d0();
    igMetaObject_NameFields(temp_s1, &DAT_004c2bd0[0], &DAT_004c2bf0[0], &DAT_004c2c10[0], temp_s0);
}
