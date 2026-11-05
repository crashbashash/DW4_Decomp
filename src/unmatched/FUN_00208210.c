struct N {
    long long q0; long long q8; char pad16[8]; struct N *next; char pad28[4]; int f32; int f36; char pad40[4]; int f44; char pad48[22];
    char lo:7; char flag:1; char f71; char f72;
};
int FUN_00204240();
extern struct N *DAT_0056c0c8[4];
struct N *FUN_00208210(void) {
    struct N *o;
    if (DAT_0056c0c8[0] == 0) {
        FUN_00204240(0xA, &DAT_0056c0c8[0]);
    }
    o = DAT_0056c0c8[0];
    DAT_0056c0c8[0] = o->next;
    o->lo = 0;
    o->q8 = 0;
    o->q0 = 0;
    o->flag = 0;
    o->f36 = 0;
    o->f32 = 0;
    o->f44 = 0;
    o->f72 = 0;
    o->f71 = 0;
    return o;
}
