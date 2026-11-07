int FUN_001e74b0();
int FUN_001e7500();
extern int DAT_0048a538[0x40];
extern int DAT_005609a8[4];
struct P { char pad[1268]; unsigned char f1268; char pad2[3]; int f1272; };
void Gap__Gfx__igPsx2VisualContext__vfunc_231(struct P *arg0, int arg1) {
    int temp_a0;

    temp_a0 = arg0->f1272;
    if ((temp_a0 != arg1) && (arg0->f1268 != 0)) {
        FUN_001e7500(DAT_0048a538[temp_a0]);
        FUN_001e74b0(DAT_0048a538[arg1]);
    }
    if (arg0->f1272 == arg1) {
        DAT_005609a8[0] += 1;
    }
    arg0->f1272 = arg1;
}
