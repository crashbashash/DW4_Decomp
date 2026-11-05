class V { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void v72(); };
struct M { char pad8[8]; int f8; char pad12[48]; int f60; char pad64[16]; int f80; };
extern "C" {
int igObject_IsKindOf(...);
unsigned int Memory_GetBufferSize(...);
int igObject_VisitFields(...);
extern int DAT_00585b20[4];
void igMemoryRefArrayMetaField_ReleaseElements(M *arg0, int arg1, int arg2, int arg3);
}
void igMemoryRefArrayMetaField_ReleaseElements(M *arg0, int arg1, int arg2, int arg3) {
    int var_s3;
    if (igObject_IsKindOf(arg0->f60, DAT_00585b20[0]) != 0) {
        for (var_s3 = 0; var_s3 < arg0->f80; var_s3++) {
            int temp_s2 = *(int *)(arg1 + arg0->f8 + var_s3 * 4);
            if (temp_s2 != 0) {
                unsigned int temp_s8 = Memory_GetBufferSize(temp_s2) >> 2;
                int var_s1;
                for (var_s1 = 0; var_s1 < (int)temp_s8; var_s1++) {
                    V **temp_s0 = (V **)(temp_s2 + var_s1 * 4);
                    if (*temp_s0 != 0) {
                        (*temp_s0)->v72();
                        igObject_VisitFields(*temp_s0, arg2, arg3);
                    }
                }
            }
        }
    }
}
