extern "C" {
int FUN_001b1030(...);
int FUN_001b1100(...);
int FUN_001b12f0(...);
int FUN_001b13d0(...);
int FUN_001d5ef0(...);
int FUN_001d9ac0(...);
int FUN_001dc500(...);
int FUN_001dc610(...);
extern int DAT_005627f8[4];
extern int DAT_00562820[4];
extern int DAT_00562840[4];
extern int DAT_00562850[4];
}
struct V4 { float x, y, z, w; };
class Ob { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void v30(V4 *); };
struct P { char p0[68]; float f68; char p72[16]; int w88; int w92; char p96[20]; Ob *o116; char p120[32]; int w152; int w156; char p160[4]; int w164; char p168[24]; int w192; int w196; char p200[37]; unsigned char b237; };
struct Q { char p0[52]; int w52; char p56[12]; int w68; };
extern "C" int FUN_001d5a70(P *arg0, Q *arg1) {
    V4 v;
    int s0 = arg1->w52;
    FUN_001dc500(arg1->w68, 0, 0);
    float w = 1.0f - arg0->f68;
    v.x = 0; v.y = 0; v.z = 0;
    v.w = w;
    arg0->o116->v30(&v);
    FUN_001b12f0(s0, DAT_00562820[0]);
    FUN_001b12f0(s0, DAT_00562850[0]);
    FUN_001b12f0(s0, arg0->w152);
    FUN_001b12f0(s0, arg0->w156);
    FUN_001b12f0(s0, arg0->w192);
    FUN_001d9ac0(arg1->w68, DAT_00562840[0], s0);
    FUN_001b13d0(s0, arg0->w192);
    FUN_001b12f0(s0, DAT_005627f8[0]);
    FUN_001b1030(s0, arg0->w88);
    FUN_001b1030(s0, arg0->w92);
    if (arg0->b237 != 0) {
        FUN_001b12f0(s0, (int)arg0->o116);
    }
    FUN_001b12f0(s0, arg0->w196);
    FUN_001d5ef0(arg0, arg1);
    FUN_001b13d0(s0, arg0->w196);
    if (arg0->b237 != 0) {
        FUN_001b13d0(s0, (int)arg0->o116);
    }
    FUN_001b1100(s0, arg0->w92);
    FUN_001b1100(s0, arg0->w88);
    FUN_001b13d0(s0, DAT_005627f8[0]);
    FUN_001b13d0(s0, arg0->w156);
    FUN_001b13d0(s0, arg0->w152);
    FUN_001b13d0(s0, DAT_00562850[0]);
    FUN_001b13d0(s0, DAT_00562820[0]);
    FUN_001dc610(arg1->w68);
    return arg0->w164;
}
