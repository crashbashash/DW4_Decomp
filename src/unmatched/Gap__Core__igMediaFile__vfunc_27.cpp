extern "C" {
int memcpy(...);
struct O;
struct A { char pad[24]; int f18; char pad2[16]; unsigned char f2c; unsigned char f2d; char pad3[6]; int f34; int f38; int f3c; O *f40; };
int Gap__Core__igMediaFile__vfunc_27(A *arg0, int arg1, int arg2, int arg3);
}
class VC_112a;
class VC_120b;
class VC_112a { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25();  virtual int vX(int, int, int); };
class VC_120b { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27();  virtual int vX(int, int, int); };
int Gap__Core__igMediaFile__vfunc_27(A *arg0, int arg1, int arg2, int arg3) {
    int bytes;
    int got;
    int n;
    int cnt;
    int back;
    if (arg0->f2d == 0) {
        return -1;
    }
    bytes = arg2 * arg3;
    if (arg0->f2c == 1) {
        got = ((VC_112a *)arg0->f40)->vX(arg0->f18, arg1, (unsigned)arg3 * arg2);
        n = got / arg2;
        back = n * arg2;
        if (got != back) {
            ((VC_120b *)arg0->f40)->vX(arg0->f18, back - got, 1);
        }
        return n;
    }
    cnt = arg3;
    if (arg0->f34 < arg0->f38 + bytes) {
        cnt = (arg0->f34 - arg0->f38) / arg2;
        bytes = cnt * arg2;
    }
    memcpy(arg1, arg0->f3c + arg0->f38, bytes, arg0->f38);
    arg0->f38 = arg0->f38 + bytes;
    return cnt;
}
