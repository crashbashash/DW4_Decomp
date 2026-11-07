/* The parameter is an int used in place; an unsigned char parameter would be normalised to a
 * masked copy. */
struct S { char pad0[1268]; unsigned char f1268; char pad1269[3]; int f1272; };
int FUN_001e74b0(int, int);
int FUN_001e7500(int, int);
extern int DAT_0048a538[4];
extern int DAT_005609a4[4];
extern unsigned char GPR_00554b58;
void Gap__Gfx__igPsx2VisualContext__vfunc_229(struct S *arg0, int arg1) {

    if (GPR_00554b58 != 0) {
        arg1 = 0;
    }
    if (arg0->f1268 == (arg1 & 0xFF)) {
        DAT_005609a4[0] += 1;
    }
    arg0->f1268 = arg1;
    if (arg1 != 0) {
        FUN_001e74b0(DAT_0048a538[arg0->f1272], arg1);
        return;
    }
    FUN_001e7500(DAT_0048a538[arg0->f1272], arg1);
}
