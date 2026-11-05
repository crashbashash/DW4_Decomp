int FUN_001d4480();
int FUN_001d4e60();
int FUN_001d5c40();
int FUN_001d6060();
struct Src { char p[96]; float f96; char p1[16]; float f116; float f120; float f124; float f128; float f132; float f136; };
struct S { char p0[32]; float f32; float f36; float f40; float f44; float f48; float f52; float f56; char p1[44]; int f104; char p2[92]; struct Src *src; };
void FUN_001d6190(struct S *arg0, char *arg1) {
    struct Src *t;
    if (arg0->f104 == 0) {
        FUN_001d4480();
        FUN_001d4e60(arg0);
        arg0->f104 = 1;
    }
    t = arg0->src;
    if (t != 0) {
        arg0->f32 = t->f116;
        arg0->f36 = t->f120;
        arg0->f40 = t->f124;
        t = arg0->src;
        arg0->f44 = t->f128;
        arg0->f48 = t->f132;
        arg0->f52 = t->f136;
        arg0->f56 = arg0->src->f96;
    }
    FUN_001d6060(arg0, arg1 + 164);
    FUN_001d5c40(arg0, arg1);
}
