struct S1304 { char pad[1304]; float f1304; int f1308; char pad2[16]; float f1328; float f1332; };
int FUN_001e8a90(int, int, float, float, float, float, float, float);
extern int DAT_0048a560[4];
extern int DAT_005609d4[4];
void Gap__Gfx__igPsx2VisualContext__vfunc_245(struct S1304 *arg0, int arg1) {
    if (arg0->f1308 == arg1) {
        DAT_005609d4[0] += 1;
    }
    arg0->f1308 = arg1;
    FUN_001e8a90(DAT_0048a560[arg0->f1308], arg0->f1308, arg0->f1328, arg0->f1332, arg0->f1304, 1.0f, 0.0f, 0.0f);
}
