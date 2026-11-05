extern "C" {
int ObjectPointerList_FindIndex(...);
int igMetaObject_FinalizeAndReplaceField(...);
void **igMetaObject_FindFieldByName(...);
int igObject_Destroy(...);
extern int DAT_004f5eb0[4];
extern void * DAT_005860d0[4];
extern int DAT_005860d8[4];
struct T { int word0; int references; int pad[5]; int f28; };
void __internalObjectList_InitFields(void);
}
class DW4VC_84_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual int vX(int); };
void __internalObjectList_InitFields(void) {
    void **temp_v0;
    int temp_s1;
    void *temp_s0;
    T *temp_v0_2;

    temp_s0 = (void *)(DAT_005860d0[0]);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s0, &DAT_004f5eb0[0]));
    temp_s1 = ObjectPointerList_FindIndex(*(int *)((char *)(temp_s0) + 40), temp_v0);
    temp_v0_2 = (T *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    *(char *)((char *)(temp_v0_2) + 66) = 1;
    temp_v0_2->f28 = (int)(&DAT_005860d8[0]);
    igMetaObject_FinalizeAndReplaceField(temp_s0, temp_s1, temp_v0_2);
    temp_v0_2->references = temp_v0_2->references - 1;
    if ((temp_v0_2->references & 0x7fffff) == 0) {
        igObject_Destroy(temp_v0_2);
    }
}
