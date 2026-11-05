typedef struct C { char pad12[12]; int f0c; } C;
typedef struct B { char pad32[32]; int f20; } B;
typedef struct A { char pad12[12]; int f0c; B *f10; C *f14; char pad24[8]; unsigned char f20; } A;
int FUN_00457e90();

void FUN_00455470(A *arg0) {
    C *temp_a0;

    if (arg0->f20 != 0) {
        temp_a0 = arg0->f14;
        if (temp_a0 != 0) {
            FUN_00457e90(temp_a0, 0);
            arg0->f14->f0c = 0;
        }
        FUN_00457e90(arg0->f0c, 0);
        arg0->f10->f20 = 0;
        arg0->f20 = 0;
    }
}
