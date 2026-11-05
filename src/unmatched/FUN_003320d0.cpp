extern "C" {
typedef struct T { char pad0[8]; int f8; int fc; char pad1[4]; int f14; char pad2[12]; unsigned char f24; char pad3[7]; int f2c; } T;
int FUN_0026b348(int, int, int);
void FUN_00331fb0(void);

int FUN_003320d0(T *arg0, int a1, int a2, int a3, int a4, int a5) {
    if (arg0->f24 == 0) {
        if (a5 != 0) {
            FUN_00331fb0();
            arg0->f24 = 1;
        } else {
            return 0;
        }
    }
    if (arg0->f2c == 0) {
        arg0->f2c = FUN_0026b348(arg0->f14, arg0->f8, arg0->fc);
        if (arg0->f2c == 0) {
            return 0;
        }
    }
    return arg0->f2c;
}
}
