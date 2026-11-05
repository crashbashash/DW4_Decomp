struct T { int w0; int refs; char pad[20]; int *f1c; };
struct G { char pad[52]; int w52; };
struct H { char pad[60]; int f60; };
extern "C" {
int FUN_002cc2c0(...);
int FUN_002ea4b0(...);
int ObjectPointerList_FindIndex(...);
int igMetaObject_CreateFields(...);
int igMetaObject_FinalizeAndReplaceField(...);
void **igMetaObject_FindFieldByName(...);
void *igMetaObject_GetFieldAt(...);
int igMetaObject_GetFieldCount(...);
int igMetaObject_NameFields(...);
int igObject_Destroy(...);
extern int DAT_004c3f30[4];
extern int DAT_004c3f70[4];
extern int DAT_004c3fb0[4];
extern int DAT_004c3ff0[4];
extern int DAT_00502570[4];
extern void * DAT_00588160[4];
extern int DAT_00588168[4];
void beSvPlatDataGC_InitFields(void);
}
class DW4VC_84_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual int vX(int); };
void beSvPlatDataGC_InitFields(void) {
    int temp_s2;
    int temp_s3;
    void **temp_v0;
    H *temp_s0;
    G *tg;
    H *temp_s0_2;
    void *temp_s1;
    T *temp_v0_2;

    temp_s1 = (void *)(DAT_00588160[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_004c3f30[0], 0xD);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, &DAT_00502570[0]));
    temp_s3 = ObjectPointerList_FindIndex(*(int *)((char *)(temp_s1) + 40), temp_v0);
    temp_v0_2 = (T *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    FUN_002ea4b0(temp_v0_2, 2);
    temp_v0_2->f1c = &DAT_00588168[0];
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s3, temp_v0_2);
    temp_v0_2->refs = temp_v0_2->refs - 1;
    if (((unsigned long long) ((long long) temp_v0_2->refs << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_v0_2);
    }
    tg = (G *)igMetaObject_GetFieldAt(temp_s1, temp_s2 + 2);
    tg->w52 = 2;
    temp_s0 = (H *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 9));
    temp_s0->f60 = FUN_002cc2c0();
    temp_s0_2 = (H *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0xB));
    temp_s0_2->f60 = FUN_002cc2c0();
    tg = (G *)igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0xC);
    tg->w52 = 0x40;
    igMetaObject_NameFields(temp_s1, &DAT_004c3f70[0], &DAT_004c3fb0[0], &DAT_004c3ff0[0], temp_s2);
}
