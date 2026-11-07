extern "C" int FUN_001e74b0(int);
extern "C" int FUN_001e7500(int);
extern long long DAT_005608b8[4];
extern unsigned char GPR_00554b54;
struct O { char pad[1228]; unsigned char v; };
extern "C" void Gap__Gfx__igPsx2VisualContext__vfunc_223(O *o, unsigned char a) {
    if (GPR_00554b54 != 0) a = 0;
    if (o->v == a) DAT_005608b8[0] += 1;
    o->v = a;
    if (a == 1) FUN_001e74b0(6);
    else FUN_001e7500(6);
}
