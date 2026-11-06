int igProperty_FindByName(int, int, void *);
extern int DAT_004e4868[4];
extern int DAT_00585be0[4];
struct S1d { int w[5]; int f20; };
int Gap__Sg__igShaderInfo__vfunc_24(struct S1d *arg0, int *arg1) {
    int r = igProperty_FindByName(arg0->f20, DAT_00585be0[0], arg1);
    if (r != 0) {
        return r;
    }
    return igProperty_FindByName(arg0->f20, DAT_00585be0[0], &DAT_004e4868[0]);
}
