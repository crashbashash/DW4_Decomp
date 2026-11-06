extern "C" {
int FUN_00232840(void);
int FUN_002cc2c0(void);
int igMetaObject_CreateFields(int, int *, int);
void *igMetaObject_GetFieldAt(int, int);
int igMetaObject_GetFieldCount(int);
int igMetaObject_NameFields(int, int *, int *, int *, int);
extern int DAT_004cbc80[4];
extern int DAT_004cbcc0[4];
extern int DAT_004cbd00[4];
extern int DAT_004cbd40[4];
extern int DAT_0058bd28[4];
void beNDMWDegiData_InitFields(void);
}
void beNDMWDegiData_InitFields(void) {
    int temp_s0;
    int temp_s2;
    void *temp_s1;
    void *temp_v0;
    void *temp_s1_2;

    temp_s0 = DAT_0058bd28[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004cbc80[0], 0xD);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    *(int *)((char *)(temp_s1) + 56) = FUN_00232840();
    *(char *)((char *)(temp_s1) + 60) = 0;
    temp_v0 = igMetaObject_GetFieldAt(temp_s0, temp_s2 + 5);
    *(int *)((char *)(temp_v0) + 52) = 0xA;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 0xC));
    *(int *)((char *)(temp_s1_2) + 60) = FUN_002cc2c0();
    igMetaObject_NameFields(temp_s0, &DAT_004cbcc0[0], &DAT_004cbd00[0], &DAT_004cbd40[0], temp_s2);
}
