class VC_156 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36();  virtual int vX(); };
class VC_120 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27();  virtual int vX(int, int, int); };
struct O;
struct A { char pad[24]; int f24; char pad2[16]; unsigned char f44; char pad3[7]; int f52; int f56; char pad4[4]; O *f64; };
extern "C" int Gap__Core__igMediaFile__vfunc_38(A *arg0, int arg1, int arg2);
int Gap__Core__igMediaFile__vfunc_38(A *arg0, int arg1, int arg2) {
    int base;
    int cur;
    if (arg0->f44 != 0) {
        base = ((VC_156 *)arg0)->vX();
        if (((VC_120 *)arg0->f64)->vX(arg0->f24, arg1, arg2) != 0) {
            return 0;
        }
        cur = ((VC_156 *)arg0)->vX();
        switch (arg2) {
        case 0:
            return -(cur != arg1);
        case 1:
            return -(arg1 != cur - base);
        case 2:
            return 0;
        default:
            return -1;
        }
    } else {
        switch (arg2) {
        case 0:
            arg0->f56 = arg1;
            break;
        case 1:
            arg0->f56 = arg0->f56 + arg1;
            break;
        case 2:
            arg0->f56 = arg0->f52 + arg1;
            break;
        default:
            return -1;
        }
        if (arg0->f56 > arg0->f52) {
            arg0->f56 = arg0->f52;
        } else if (arg0->f56 < 0) {
            arg0->f56 = 0;
        }
        return 0;
    }
}
