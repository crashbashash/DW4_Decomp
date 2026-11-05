int FUN_001f8aa0();
extern int DAT_00560918[4];
struct O { char p[88]; float v[4]; };
struct H { char p[1344]; struct O *o; };
void FUN_00172230(struct H *arg0, float *arg1) {
    float *a2;
    struct O *o;
    int r;
    o = arg0->o;
    r = 1;
    a2 = o->v;
    if (o->v[0] != arg1[0]) r = 0;
    if (r != 0) { r = 1; if (a2[1] != arg1[1]) r = 0; }
    if (r != 0) { r = 1; if (a2[2] != arg1[2]) r = 0; }
    if (r != 0) { r = 1; if (a2[3] != arg1[3]) r = 0; }
    if (r != 0) {
        DAT_00560918[0] += 1;
    }
    o = arg0->o;
    o->v[0] = arg1[0];
    o->v[1] = arg1[1];
    o->v[2] = arg1[2];
    o->v[3] = arg1[3];
    FUN_001f8aa0(arg1);
}
