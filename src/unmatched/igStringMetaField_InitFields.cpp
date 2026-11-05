extern "C" {
int FUN_002d3890(...);
int FUN_002d4e40(...);
int ObjectPointerList_FindIndex(...);
int igMetaObject_CreateFields(...);
int igMetaObject_FinalizeAndReplaceField(...);
void **igMetaObject_FindFieldByName(...);
void *igMetaObject_GetFieldAt(...);
int igMetaObject_GetFieldCount(...);
int igMetaObject_NameFields(...);
int igObject_Destroy(...);
extern int DAT_004bf6a0[4];
extern int DAT_004bf6a8[4];
extern int DAT_004bf6b0[4];
extern int DAT_004bf6b8[4];
extern int DAT_004f5f20[4];
extern int DAT_004f5f38[4];
extern void * DAT_00585908[4];
extern int DAT_00585918[4];
extern int DAT_00585920[4];
struct M { int pad[10]; int f40; };
struct T { int word0; int references; int pad[5]; int f28; };
void igStringMetaField_InitFields(void);
}
class DW4VC_84_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual int vX(int); };
void igStringMetaField_InitFields(void) {
    int temp_s2;
    int temp_s3;
    void **temp_v0;
    M *temp_s1;
    T *temp_v0_2;
    T *temp_v0_4;

    temp_s1 = (M *)(DAT_00585908[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_004bf6a0[0], 1);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, &DAT_004f5f20[0]));
    temp_s3 = ObjectPointerList_FindIndex(temp_s1->f40, temp_v0);
    temp_v0_2 = (T *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    FUN_002d4e40(temp_v0_2, 2);
    temp_v0_2->f28 = (int)(&DAT_00585918[0]);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s3, temp_v0_2);
    temp_v0_2->references = temp_v0_2->references - 1;
    if (((unsigned long long)(long long)temp_v0_2->references & 0x7fffffULL) == 0) {
        igObject_Destroy(temp_v0_2);
    }
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, &DAT_004f5f38[0]));
    temp_s3 = ObjectPointerList_FindIndex(temp_s1->f40, temp_v0);
    temp_v0_4 = (T *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    FUN_002d3890(temp_v0_4, 1);
    temp_v0_4->f28 = (int)(&DAT_00585920[0]);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s3, temp_v0_4);
    temp_v0_4->references = temp_v0_4->references - 1;
    if (((unsigned long long)(long long)temp_v0_4->references & 0x7fffffULL) == 0) {
        igObject_Destroy(temp_v0_4);
    }
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s1, temp_s2), 1);
    igMetaObject_NameFields(temp_s1, &DAT_004bf6a8[0], &DAT_004bf6b0[0], &DAT_004bf6b8[0], temp_s2);
}
