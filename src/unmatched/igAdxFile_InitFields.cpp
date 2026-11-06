/* Thunk address spelled as a function declaration (absolute lui/addiu, not gp-relative). */
extern "C" {
int FUN_002d3890(int, int);
int FUN_002ea4b0(int, int);
int FUN_002fe480(int (*)(void));
int FUN_0030ec10(int, int);
int igMetaObject_CreateFields(void *, int *, int);
int igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
int FUN_003350d0(void);
int thunk_igFile_GetMetaObject(void);
extern int DAT_004c26c0[4];
extern int DAT_004c2700[4];
extern int DAT_004c2740[4];
extern int DAT_004c2780[4];
extern void * DAT_00587668[4];
void igAdxFile_InitFields(void);
}
void igAdxFile_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)(DAT_00587668[0]);
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c26c0[0], 0xE);
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 4), 1);
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 5), 1);
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 6), 1);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 8), 0x20000);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xC), 0x800);
    FUN_0030ec10(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xD), 0xFE502A);
    igMetaObject_NameFields(temp_s0, &DAT_004c2700[0], &DAT_004c2740[0], &DAT_004c2780[0], temp_s1);
    *(int *)((char *)(DAT_00587668[0]) + 64) = (int)(&thunk_igFile_GetMetaObject);
    FUN_002fe480(&FUN_003350d0);
}
