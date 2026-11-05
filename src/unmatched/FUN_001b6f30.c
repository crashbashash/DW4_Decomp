int FUN_001b0000();
int igObject_Destroy();
extern int DAT_0055f468[4];

typedef struct R { int w0; int refs; } R;
typedef struct A { char pad[32]; R *f32; R *f36; char pad40[12]; int f52; } A;

void FUN_001b6f30(A *arg0, R *arg1, R *arg2) {
    R *temp_a0;
    R *temp_a0_2;

    if (arg2 != 0) {
        arg2->refs = arg2->refs + 1;
    }
    temp_a0 = arg0->f32;
    if (temp_a0 != 0) {
        temp_a0->refs = temp_a0->refs - 1;
        if (((unsigned long long)((long long)temp_a0->refs << 0x29) >> 0x29) == 0) {
            igObject_Destroy(temp_a0);
        }
    }
    arg0->f32 = arg2;
    if (arg1 != 0) {
        arg1->refs = arg1->refs + 1;
    }
    temp_a0_2 = arg0->f36;
    if (temp_a0_2 != 0) {
        temp_a0_2->refs = temp_a0_2->refs - 1;
        if (((unsigned long long)((long long)temp_a0_2->refs << 0x29) >> 0x29) == 0) {
            igObject_Destroy(temp_a0_2);
        }
    }
    arg0->f36 = arg1;
    FUN_001b0000(arg0->f52, DAT_0055f468[0], arg0->f36, arg0->f32);
}
