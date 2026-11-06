extern "C" {
int Gap__Attrs__igTextureAttr__vfunc_24(...);
void Gap__Attrs__igTextureCubeAttr__vfunc_24(int *arg0, int *arg1);
}
class VA { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual int v96(int *); };
class VB { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual int v148(int,int); };
void Gap__Attrs__igTextureCubeAttr__vfunc_24(int *arg0, int *arg1) {
    int a4 = arg0[9];
    if (a4 < 0) {
        switch (arg0[24]) {
        case 0:
            if (((VB *)arg1)->v148(0x15, 2) != 0 && arg0[18] != 0) {
                arg0[24] = 1;
            } else {
                arg0[24] = 2;
            }
            ((VA *)arg0)->v96(arg1);
            break;
        case 1:
            if (a4 < 0) {
                arg0[24] = 2;
                ((VA *)arg0)->v96(arg1);
            }
            break;
        case 2:
            Gap__Attrs__igTextureAttr__vfunc_24();
            break;
        }
        if (arg0[9] >= 0) {
            goto b14;
        }
    } else {
b14:
        Gap__Attrs__igTextureAttr__vfunc_24(arg0, arg1);
    }
}
