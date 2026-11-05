extern "C" int FUN_0010f738(int, int, int);
class Obj { public:  virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36();  virtual int vX(); };
extern "C" int Gap__Core__igPsx2File__vfunc_38(int *arg0, int arg1, int arg2);
extern "C" int Gap__Core__igPsx2File__vfunc_38(int *arg0, int arg1, int arg2) {
    int s;
    if (arg0[15] != 0) {
        switch (arg2) {
        case 0:
            s = FUN_0010f738(arg0[6], arg1, 0);
            return -(s != arg1);
        case 1:
            s = ((Obj *)arg0)->vX();
            return -(arg1 != FUN_0010f738(arg0[6], arg1, 1) - s);
        case 2:
            FUN_0010f738(arg0[6], arg1, 2);
            return 0;
        default:
            return -1;
        }
    } else {
        switch (arg2) {
        case 0:
            arg0[13] = arg1;
            break;
        case 1:
            arg0[13] = arg0[13] + arg1;
            break;
        case 2:
            arg0[13] = arg0[14] + arg1;
            break;
        default:
            return -1;
        }
        {int v1 = arg0[14]; int v0 = arg0[13];
        if (v1 < v0) arg0[13] = v1;
        else if (v0 < 0) arg0[13] = 0;}
        return 0;
    }
}
