struct O { char pad[28]; char f1c; char pad2[131]; unsigned char fa0; char pad3[11]; int fac; };
struct P { char pad[12]; struct O *o; };
int FUN_004578c0();
extern int DAT_0058c3e0[4];
int FUN_00457220(struct P *arg0, int arg1, char arg2) {
    int sp[3];
    struct O *o;

    o = arg0->o;
    if (o->fa0 == 0) {
        return 0;
    }
    if (arg1 != 0) {
        return 0;
    }
    o->f1c = arg2;
    sp[0] = 2;
    sp[1] = 0;
    sp[2] = DAT_0058c3e0[0];
    FUN_004578c0(arg0->o, &sp[0]);
    return arg0->o->fac != 0;
}
