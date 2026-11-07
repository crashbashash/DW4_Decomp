extern int DAT_0056099c[4];
int FUN_001747f0();
struct S { char pad[1028]; float f; };
void Gap__Gfx__igPsx2VisualContext__vfunc_221(struct S *arg0, float fparg0) {
    if (arg0->f == fparg0) {
        DAT_0056099c[0] += 1;
    }
    arg0->f = fparg0;
    FUN_001747f0();
}
