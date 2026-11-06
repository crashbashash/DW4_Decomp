typedef struct S0 { char pad12[12]; int fC; char f10; char pad128[111]; int f80; int f84; int f88; } S0;
int FUN_001eee30();
int FUN_001eef20();
int Gap__Core__igObject__vfunc_15();

void Gap__Gfx__igPsx2VertexStream__vfunc_17(S0 *arg0) {
    Gap__Core__igObject__vfunc_15();
    if ((arg0->f84 != 0) && (arg0->f88 != 0)) {
        arg0->f10 = 1;
        arg0->f80 = FUN_001eef20(arg0->f84, arg0->f88);
        arg0->fC = FUN_001eee30(arg0->f80);
    }
}
