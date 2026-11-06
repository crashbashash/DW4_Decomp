typedef struct S1 { char pad4[4]; int f4; } S1;
typedef struct A { char pad8[8]; int f8; char pad12[41]; unsigned char f35; char pad54[14]; int f44; } A;
int igObject_Destroy();

void Gap__Core__igObjectRefArrayMetaField__vfunc_32(A *arg0, int arg1) {
    int i;
    S1 *temp_a0;

    if (arg0->f35 != 0) {
        for (i = 0; i < arg0->f44; i++) {
            temp_a0 = *(S1 **)(arg1 + arg0->f8 + (i * 4));
            if (temp_a0 != 0) {
                temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
                if (((unsigned long long) ((long long) temp_a0->f4 << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(temp_a0);
                }
            }
        }
    }
}
