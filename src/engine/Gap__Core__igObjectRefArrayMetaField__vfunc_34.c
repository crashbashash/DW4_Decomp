int igObject_Destroy();
int igRefMetaField_ClearValue();

typedef struct R { int w0; int refs; } R;
typedef struct S { char pad0[8]; int f8; char pad12[26]; unsigned char f38; char pad39[21]; unsigned char f60; char pad61[7]; int f68; } S;

void Gap__Core__igObjectRefArrayMetaField__vfunc_34(S *arg0, int arg1) {
    int var_s0;
    R *temp_a0;

    if (arg0->f38 != 0) {
        if (arg0->f60 != 0) {
            for (var_s0 = 0; var_s0 < arg0->f68; var_s0++) {
                temp_a0 = *(R **)(arg1 + arg0->f8 + (var_s0 * 4));
                if (temp_a0 != 0) {
                    temp_a0->refs = temp_a0->refs - 1;
                    if (((unsigned long long)((long long)temp_a0->refs << 0x29) >> 0x29) == 0) {
                        igObject_Destroy(temp_a0);
                    }
                }
            }
        }
        igRefMetaField_ClearValue(arg0, arg1);
    }
}
