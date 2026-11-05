extern "C" {
void *FUN_002d7e90(...);
void **igIntMetaField_GetDefaultDescriptor(...);
int igRefMetaField_ReadRawFieldMem(void *arg0, int a1, int *arg2, int arg3, int arg4);
}
struct DW4SR4 { int w0; };
class DW4VCSR_208_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void vX(int *, int); };
int igRefMetaField_ReadRawFieldMem(void *arg0, int a1, int *arg2, int arg3, int arg4) {
    DW4SR4 sp3C;
    int *arg1 = (int *)a1;
    int temp_v1;
    void **temp_v0;
    void *temp_v0_2;

    if ((arg3 != 0) && (temp_v1 = *arg2, (temp_v1 != -1))) {
        sp3C.w0 = temp_v1;
        if (arg4 != 0) {
            temp_v0 = (void **)(igIntMetaField_GetDefaultDescriptor());
            ((DW4VCSR_208_1 *)(temp_v0))->vX(&sp3C.w0, 1);
        }
        temp_v0_2 = (void *)(FUN_002d7e90(arg3, sp3C.w0));
        if (temp_v0_2 != 0) {
            *arg1 = *(int *)((char *)(temp_v0_2) + 24);
        } else {
            *arg1 = 0;
        }
    } else {
        *arg1 = 0;
    }
    return 4;
}
