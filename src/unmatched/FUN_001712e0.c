typedef struct E { char pad76[76]; float f76; char pad80[80]; } E;
typedef struct L { char pad16[16]; E *f16; } L;
typedef struct S { char pad1336[1336]; L *f1336; } S;
int FUN_00171690();
extern int DAT_005608e8[4];
void FUN_001712e0(S *arg0, int arg1, float fparg0) {
    float temp_f1;
    E *temp_a1;
    L *temp_a2;

    temp_a2 = arg0->f1336;
    temp_a1 = temp_a2->f16 + arg1;
    if (temp_a1 != 0) {
        temp_f1 = 128.0f * fparg0;
        if (temp_a1->f76 == temp_f1) {
            DAT_005608e8[0] += 1;
        }
        temp_a1->f76 = temp_f1;
        FUN_00171690(arg0, temp_a1);
    }
}
