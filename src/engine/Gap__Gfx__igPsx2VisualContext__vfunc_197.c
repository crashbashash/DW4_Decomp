int FUN_001e9740();
struct S { char pad[72]; int f72; int f76; int pad2; int f84; char pad3[1336]; char f1424; };
void Gap__Gfx__igPsx2VisualContext__vfunc_197(struct S *arg0, int arg1, int arg2) {
    arg0->f72 = arg1;
    arg0->f84 = arg2;
    arg0->f1424 = 1;
    arg0->f76 = arg0->f76 + 1;
    FUN_001e9740(arg0->f84, arg0->f72);
}
