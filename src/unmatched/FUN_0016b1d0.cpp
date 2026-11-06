extern "C" {
int FUN_001ea420(int);
int FUN_001ea8a0(int);
int FUN_001f05a0(int, int);
int FUN_0020b270(int);
int FUN_0020c9f0(int);
}
struct E8 { int p0; int p4; int w8; int p12[3]; };
struct T { unsigned short f0; short pad; unsigned short f4; short pad2; int f8; unsigned short *f12; E8 *f16;
    bool Chk(int s0) {
        int a2, a1;
        if (s0 < f0 && s0 >= 0) {
            a1 = f4;
            for (a2 = 0; a2 < a1; a2++) {
                if (s0 == f12[a2]) return false;
            }
            return true;
        }
        return false;
    }
};
struct O { int w[82]; T *f328; int p332[3]; int f344; };
extern "C" void FUN_0016b1d0(O *arg0, int arg1);
void FUN_0016b1d0(O *arg0, int arg1) {
    T *t;
    int h;
    E8 *e;
    t = arg0->f328;
    if (t->Chk(arg1)) {
        e = t->f16 + arg1;
        if (e->w8 != 0) {
            h = FUN_001ea420(e->w8);
            FUN_001f05a0(2, FUN_0020b270(h));
            FUN_0020c9f0(h);
            FUN_001ea8a0(e->w8);
        }
        e->w8 = 0;
        arg0->f344 = -1;
    }
}
