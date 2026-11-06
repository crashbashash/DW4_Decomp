/* Refcount release written as -= 1 with the 23-bit mask on a typed struct.py. */
extern "C" {
int igUnsignedIntMetaField_GetDefaultDescriptor(...);
int ObjectPointerList_FindIndex(...);
int igMemoryRefMetaField_SetDefaultWord(...);
int igMetaObject_FinalizeAndReplaceField(...);
void **igMetaObject_FindFieldByName(...);
int igObject_Destroy(...);
extern int DAT_004dbec8[4];
extern void * DAT_0055fb00[4];
extern int DAT_0055fb08[4];
void igPrimLengthArray1_1_InitFields(void);
}
struct T { int vt; int ref; char pad8[20]; int f28; char pad32[21]; char f53; char pad54[2]; int f56; int f60; char f64; char f65; };
class DW4VC_84_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual T *vX(int); };
extern "C" void igPrimLengthArray1_1_InitFields(void) {
    void **temp_v0;
    T *temp_s0;
    void *temp_s1;
    int temp_s2;

    temp_s1 = (void *)(DAT_0055fb00[0]);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, &DAT_004dbec8[0]));
    temp_s2 = ObjectPointerList_FindIndex(*(int *)((char *)(temp_s1) + 40), temp_v0);
    temp_s0 = ((DW4VC_84_1 *)(temp_v0))->vX(1);
    temp_s0->f60 = igUnsignedIntMetaField_GetDefaultDescriptor();
    temp_s0->f56 = 0;
    igMemoryRefMetaField_SetDefaultWord(temp_s0, 0);
    temp_s0->f53 = 1;
    temp_s0->f64 = 1;
    temp_s0->f65 = 1;
    temp_s0->f28 = (int)(&DAT_0055fb08[0]);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s2, temp_s0);
    temp_s0->ref -= 1;
    if ((temp_s0->ref & 0x7fffff) == 0) {
        igObject_Destroy(temp_s0);
    }
}
