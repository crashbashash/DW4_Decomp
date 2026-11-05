extern "C" {
int FUN_002ea4b0(...);
int ObjectPointerList_FindIndex(...);
int igMetaObject_FinalizeAndReplaceField(...);
void **igMetaObject_FindFieldByName(...);
int igObject_Destroy(...);
extern int DAT_005027d8[4];
extern void * DAT_005881e0[4];
extern int DAT_005881e8[4];
void beSvEndApi_InitFields(void);
}
struct SR { char pad4[4]; int f4; };
class DW4VC_84_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual int vX(int); };
void beSvEndApi_InitFields(void) {
    int temp_s2;
    void **temp_v0;
    void *temp_s1;
    void *temp_v0_2;

    temp_s1 = (void *)(DAT_005881e0[0]);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, &DAT_005027d8[0]));
    temp_s2 = ObjectPointerList_FindIndex(*(int *)((char *)(temp_s1) + 40), temp_v0);
    temp_v0_2 = (void *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    FUN_002ea4b0(temp_v0_2, 0xB);
    *(int *)((char *)(temp_v0_2) + 28) = (int)(&DAT_005881e8[0]);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s2, temp_v0_2);
    ((SR *)temp_v0_2)->f4 = ((SR *)temp_v0_2)->f4 - 1;
    if ((((SR *)temp_v0_2)->f4 & 0x7FFFFF) == 0) {
        igObject_Destroy(temp_v0_2);
    }
}
