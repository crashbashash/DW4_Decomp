int FUN_001e8be0();
extern int DAT_005609e8[4];
extern int DAT_0048a520[4];
struct S { char p[1428]; int idx; float v[4]; };
void FUN_00175510(struct S *arg0, float *arg1) {
    int r = 1;
    if (arg0->v[0] != arg1[0]) r = 0;
    if (r != 0) { r = 1; if (arg0->v[1] != arg1[1]) r = 0; }
    if (r != 0) { r = 1; if (arg0->v[2] != arg1[2]) r = 0; }
    if (r != 0) { r = 1; if (arg0->v[3] != arg1[3]) r = 0; }
    if (r != 0) {
        DAT_005609e8[0] += 1;
    }
    arg0->v[0] = arg1[0];
    arg0->v[1] = arg1[1];
    arg0->v[2] = arg1[2];
    arg0->v[3] = arg1[3];
    FUN_001e8be0(DAT_0048a520[arg0->idx], arg0->v);
}
