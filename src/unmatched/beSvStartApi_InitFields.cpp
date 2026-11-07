extern "C" {
int FUN_002ea4b0(...);
int ObjectPointerList_FindIndex(...);
int igMetaObject_FinalizeAndReplaceField(...);
void **igMetaObject_FindFieldByName(...);
int igObject_Destroy(...);
extern int DAT_005027d8[4];
extern void * DAT_005881f0[4];
extern int DAT_005881f8[4];
void beSvStartApi_InitFields(void);
}
struct T { int word0; int references; int pad[5]; int f28; };
class DW4VC_84_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual int vX(int); };
void beSvStartApi_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void **temp_v0;
    T *temp_v0_2;

    temp_s1 = (void *)(DAT_005881f0[0]);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, &DAT_005027d8[0]));
    temp_s2 = ObjectPointerList_FindIndex(*(int *)((char *)(temp_s1) + 40), temp_v0);
    temp_v0_2 = (T *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    FUN_002ea4b0(temp_v0_2, 0xA);
    temp_v0_2->f28 = (int)(&DAT_005881f8[0]);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s2, temp_v0_2);
    temp_v0_2->references = temp_v0_2->references - 1;
    if (((unsigned long long)(long long)temp_v0_2->references & 0x7fffffULL) == 0) {
        igObject_Destroy(temp_v0_2);
    }
}
