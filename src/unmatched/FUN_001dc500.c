typedef struct L2 { char pad[8]; int f8; int f12; } L2;
typedef struct X { char pad[4]; int f4; int f8; int f12; char pad2[12]; L2 *f28; } X;
typedef struct L { char pad[8]; int f8; char pad2[4]; X **f16; int f20; } L;
typedef struct A { char pad[16]; L *f16; char pad2[92]; unsigned char f112; char f113; char f114; char pad3; X *f116; int f120; } A;
int FUN_001dca40();
int List_Resize();
int igObject_Destroy();
int FUN_00197ab0();

void FUN_001dc500(A *arg0, char arg1, char arg2) {
    int temp_a0;
    L *temp_s0;
    X *temp_s0_2;
    X *t;
    L2 *temp_a0_3;

    arg0->f120 = arg0->f120 + 1;
    if (arg0->f112 == 0) {
        arg0->f112 = 1;
        arg0->f113 = arg1;
        arg0->f114 = arg2;
        temp_s0 = arg0->f16;
        if (temp_s0->f20 >= temp_s0->f8) {
            FUN_001dca40(temp_s0, &FUN_00197ab0);
        }
        temp_a0 = temp_s0->f20;
        temp_s0->f20 = temp_a0 + 1;
        temp_s0_2 = temp_s0->f16[temp_a0];
        temp_s0_2->f12 = temp_s0_2->f8;
        if (temp_s0_2 != 0) {
            temp_s0_2->f4 = temp_s0_2->f4 + 1;
        }
        t = arg0->f116;
        if (t != 0) {
            t->f4 = t->f4 - 1;
            if (((unsigned long long) ((long long) t->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(t);
            }
        }
        arg0->f116 = temp_s0_2;
        temp_a0_3 = arg0->f116->f28;
        if (0 <= temp_a0_3->f12) {
            temp_a0_3->f8 = 0;
            return;
        }
        List_Resize(temp_a0_3, 0, 4);
    }
}
