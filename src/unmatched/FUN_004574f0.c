typedef struct E { char pad4[4]; int f4; int f8; int f12; } E;
typedef struct LST { char pad8[8]; int f8; char pad12[4]; E **f16; } LST;
typedef struct T { char pad8[8]; LST *f8; } T;
int List_RemoveWordAt();
int igObject_Destroy();

void FUN_004574f0(T *arg0, int arg1) {
    E *temp_a0;
    int var_s1;
    LST *temp_s0;

    for (var_s1 = arg0->f8->f8 - 1; var_s1 >= 0; var_s1 -= 1) {
        temp_s0 = arg0->f8;
        temp_a0 = temp_s0->f16[var_s1];
        if (temp_a0->f12 == arg1) {
            if (temp_a0->f8 == 0) {
                if (temp_a0 != 0) {
                    temp_a0->f4 = temp_a0->f4 - 1;
                    if (((unsigned long long) ((long long) temp_a0->f4 << 0x29) >> 0x29) == 0) {
                        igObject_Destroy(temp_a0);
                    }
                }
                List_RemoveWordAt(temp_s0, var_s1);
                temp_s0->f16[temp_s0->f8] = 0;
            } else {
                temp_a0->f12 = 0x20;
            }
        }
    }
}
