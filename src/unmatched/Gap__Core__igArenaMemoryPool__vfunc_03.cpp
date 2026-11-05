extern "C" {
int memset(...);
int FUN_00308320(...);
int Gap__Core__igObject__vfunc_01(...);
extern int DAT_004fd640[4];
extern int DAT_00587200[4];
struct P { char pad[2020]; void *f7e4; int f7e8; int f7ec; int f7f0; char pad2[24]; int f80c; int f810; };
struct A { char pad[112]; P *f70; };
extern unsigned char GPR_00554d7c;
}
class V { public: virtual void d0(); virtual void d1(); virtual P *vA(int); virtual void d2(); virtual void *vB(int, int); };
extern V *DAT_00587218[4];
extern "C" void Gap__Core__igArenaMemoryPool__vfunc_03(A *arg0, int arg1);
void Gap__Core__igArenaMemoryPool__vfunc_03(A *arg0, int arg1) {
    int t;
    arg0->f70 = DAT_00587218[0]->vA(0x814);
    memset(arg0->f70, 0, 0x814);
    if (arg0->f70->f7e4 == 0) {
        arg0->f70->f7e4 = DAT_00587218[0]->vB(0x200, 4);
        if (arg0->f70->f7e4 == 0 && GPR_00554d7c == 0) {
            t = FUN_00308320(&DAT_004fd640[0]);
            if (t != 1 && t == 2) {
                GPR_00554d7c = 1;
            }
        }
        arg0->f70->f7e8 = 0x200;
        arg0->f70->f7ec = 0;
        arg0->f70->f7f0 = 0;
        arg0->f70->f80c = -1;
        arg0->f70->f810 = 0;
    }
    DAT_00587200[0] += 1;
    Gap__Core__igObject__vfunc_01(arg0, arg1);
}
