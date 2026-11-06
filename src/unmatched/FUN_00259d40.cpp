/* Virtual call with a hidden struct-return pointer; alternate compiler -O3,p. */
extern "C" {
int FUN_00259dc0(...);
extern int DAT_0056df78[4];
extern void * DAT_005871d0[4];
extern unsigned char GPR_00554990;
extern unsigned char GPR_00554be8;
extern unsigned char GPR_00554bec;
void FUN_00259d40(int arg0, int arg1);
}
struct R { int a; };
class VC { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual R vX(int); };

void FUN_00259d40(int arg0, int arg1) {
    int sp2C;
    VC *temp_a1;

    if (GPR_00554bec != 0) {
        if (arg1 != 0) {
            temp_a1 = (VC *)(**(int **)((char *)(*(int *)((char *)(DAT_005871d0[0]) + 8)) + 16));
            temp_a1->vX(0xF4240);
        }
        if (GPR_00554be8 != 0) {
            FUN_00259dc0(arg0, DAT_0056df78[0], GPR_00554990);
            GPR_00554990 = 0;
            GPR_00554be8 = 0;
        }
    }
}
