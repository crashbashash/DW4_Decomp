/* C++ translation unit: the unit compiled with exceptions on and retail keeps this function's
 * exception index record, which only the C++ front end emits. */
extern "C" {
int FUN_002d3890(void *, int);
int FUN_002e3810(void *, float);
int FUN_00368a30(void);
int FUN_00459380(void);
int FUN_0045b420(void);
int igMetaObject_CreateFields(void *, int *, int);
void *igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c7a60[4];
extern int DAT_004c7aa0[4];
extern int DAT_004c7ae0[4];
extern int DAT_004c7b20[4];
extern int DAT_00589c90[4];
void beCameraCtrl_InitFields(void);
}
void beCameraCtrl_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s1_2;
    void *temp_s1_3;
    void *temp_s0;

    temp_s0 = (void *)DAT_00589c90[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c7a60[0], 0xD);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    *(int *)((char *)(temp_s1) + 56) = FUN_00459380();
    *(char *)((char *)(temp_s1) + 60) = 0;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    *(int *)((char *)(temp_s1_2) + 56) = FUN_0045b420();
    *(char *)((char *)(temp_s1_2) + 60) = 0;
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    *(int *)((char *)(temp_s1_3) + 56) = FUN_00368a30();
    FUN_002e3810(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 0xB), 1.0f);
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 0xC), 1);
    igMetaObject_NameFields(temp_s0, &DAT_004c7aa0[0], &DAT_004c7ae0[0], &DAT_004c7b20[0], temp_s2);
}
