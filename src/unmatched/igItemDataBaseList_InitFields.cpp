extern "C" {
int FUN_00228570(...);
int ObjectPointerList_FindIndex(...);
int igMetaObject_FinalizeAndReplaceField(...);
void **igMetaObject_FindFieldByName(...);
int igObject_Destroy(...);
extern int DAT_004e79a8[4];
extern void * DAT_0056d9c8[4];
extern int DAT_0056d9d0[4];
void igItemDataBaseList_InitFields(void);
}
class DW4VC_84_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual int vX(int); };
struct S_obj { char pad4[4]; int f4; char pad8[20]; int f28; char pad32[24]; int f56; int f60; };
void igItemDataBaseList_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void **temp_v0;
    S_obj *temp_s0;

    temp_s1 = (void *)(DAT_0056d9c8[0]);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, &DAT_004e79a8[0]));
    temp_s2 = ObjectPointerList_FindIndex(*(int *)((char *)(temp_s1) + 40), temp_v0);
    temp_s0 = (S_obj *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    temp_s0->f60 = FUN_00228570();
    temp_s0->f56 = 0;
    temp_s0->f28 = (int)(&DAT_0056d9d0[0]);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s2, temp_s0);
    temp_s0->f4 = temp_s0->f4 - 1;
    if (((unsigned long long) ((long long) temp_s0->f4 << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_s0);
    }
}
