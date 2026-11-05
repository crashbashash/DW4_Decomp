struct T { int w0; int refs; char pad[20]; int *f1c; };
struct F { char pad[52]; unsigned char b52; char pad2[3]; int f56; };
struct G { char pad[52]; int w52; };
extern "C" {
int FUN_002ea4b0(...);
int FUN_00347600(...);
int ObjectPointerList_FindIndex(...);
int igMetaObject_CreateFields(...);
int igMetaObject_FinalizeAndReplaceField(...);
void **igMetaObject_FindFieldByName(...);
void *igMetaObject_GetFieldAt(...);
int igMetaObject_GetFieldCount(...);
int igMetaObject_NameFields(...);
int igObject_Destroy(...);
extern int DAT_004c3d20[4];
extern int DAT_004c3d30[4];
extern int DAT_004c3d40[4];
extern int DAT_004c3d50[4];
extern int DAT_00502570[4];
extern void * DAT_00588040[4];
extern int DAT_00588048[4];
void beSvPlatDataXbox_InitFields(void);
}
class DW4VC_84_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual int vX(int); };
void beSvPlatDataXbox_InitFields(void) {
    int temp_s2;
    int temp_s3;
    void **temp_v0;
    F *temp_s0;
    G *tg;
    void *temp_s1;
    T *temp_v0_2;

    temp_s1 = (void *)(DAT_00588040[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_004c3d20[0], 4);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, &DAT_00502570[0]));
    temp_s3 = ObjectPointerList_FindIndex(*(int *)((char *)(temp_s1) + 40), temp_v0);
    temp_v0_2 = (T *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    FUN_002ea4b0(temp_v0_2, 9);
    temp_v0_2->f1c = &DAT_00588048[0];
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s3, temp_v0_2);
    temp_v0_2->refs = temp_v0_2->refs - 1;
    if (((unsigned long long) ((long long) temp_v0_2->refs << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_v0_2);
    }
    temp_s0 = (F *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 1));
    temp_s0->f56 = FUN_00347600();
    temp_s0->b52 = 1;
    tg = (G *)igMetaObject_GetFieldAt(temp_s1, temp_s2 + 3);
    tg->w52 = 2;
    igMetaObject_NameFields(temp_s1, &DAT_004c3d30[0], &DAT_004c3d40[0], &DAT_004c3d50[0], temp_s2);
}
