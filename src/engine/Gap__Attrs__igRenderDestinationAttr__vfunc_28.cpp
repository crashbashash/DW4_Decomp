typedef struct R { int w0; int refs; } R;
class DW4VC_188 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual int vX(int); };
struct X { char pad0[12]; int w12; char pad1[4]; int w20; char pad2[40]; R *obj; };
extern "C" {
int igObject_Destroy(...);
void Gap__Attrs__igRenderDestinationAttr__vfunc_28(X *arg0);
}
void Gap__Attrs__igRenderDestinationAttr__vfunc_28(X *arg0) {
    int temp_a1;
    R *temp_a0;
    R *temp_a0_2;

    if (arg0->w12 != 2) {
        temp_a0 = arg0->obj;
        if (temp_a0 != 0) {
            temp_a1 = arg0->w20;
            if (temp_a1 >= 0) {
                ((DW4VC_188 *)temp_a0)->vX(temp_a1);
            }
        }
        temp_a0_2 = arg0->obj;
        if (temp_a0_2 != 0) {
            temp_a0_2->refs = temp_a0_2->refs - 1;
            if (((unsigned long long)((long long)temp_a0_2->refs << 0x29) >> 0x29) == 0) {
                igObject_Destroy(temp_a0_2);
            }
        }
        arg0->obj = 0;
        arg0->w20 = -1;
    }
}
