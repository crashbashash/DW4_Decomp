extern "C" {
int FUN_0026d5f0(int, short, short);
int FUN_0026d7a0(int, int);
int FUN_003321f0(struct A *, int, int, int, int, int);
int FUN_00333440(int);
extern void * DAT_00587620[4];
struct A { char pad[20]; int f20; int f24; int f28; int f32; char pad2[8]; int f44; };
struct L { char pad[16]; int *tab; };
struct E { char pad[16]; short s16; short s18; };
int FUN_00332290(struct A *arg0, int arg1) {
    int temp_v0;
    struct E *e;

    if (arg0->f44 != 0) {
        temp_v0 = FUN_00333440(arg1);
        if (temp_v0 != -1) {
            e = (struct E *)((struct L *)DAT_00587620[0])->tab[temp_v0];
            FUN_0026d5f0(arg0->f44, e->s16, e->s18);
        } else {
            FUN_0026d7a0(arg0->f44, arg1);
        }
        return 1;
    }
    return FUN_003321f0(arg0, arg1, arg0->f20, arg0->f24, arg0->f28, arg0->f32);
}
}
