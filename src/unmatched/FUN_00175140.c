void FUN_001e8a90(int, int, float, float, float, float, float, float);
extern int DAT_0048a560[4];
extern int DAT_005609d0[4];
struct S { char p[1304]; float f1304; int f1308; char q[16]; float f1328; float f1332; };
void FUN_00175140(struct S *arg0, float fparg0) {
    int i;
    if (arg0->f1304 == fparg0) {
        DAT_005609d0[0] += 1;
    }
    arg0->f1304 = fparg0;
    i = arg0->f1308;
    FUN_001e8a90(DAT_0048a560[i], i, arg0->f1328, arg0->f1332, arg0->f1304, 1.0f, 0.0f, 0.0f);
}
