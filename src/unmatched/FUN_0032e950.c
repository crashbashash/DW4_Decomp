/* 0x0032e950 - FUN_0032e950. eight-argument setup, member address kept in a pointer local for the later read; alternate compiler -O3. Verified byte-identical by tools/verify.py. */
int FUN_0010b7d8(int, int);
int FUN_0032d6d0(int *, int, int, void *, int, void *, int, int);
struct T { int f0, f4, f8, f12, f16, f20, f24, f28, f32; };
struct E { char pad[12]; int f12; };
struct Z { char pad[8]; int f8; int f12; char padx[4]; struct T *f20; char pad2[4]; struct E *f28; };
int FUN_0032e950(struct Z *arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7) {
    int sp4C;
    int temp_a0;
    struct T *temp_s1;
    int *p;
    temp_s1 = arg0->f20;
    p = &temp_s1->f32;
    temp_s1->f0 = *(int *)(arg0->f28->f12 + arg1 * 12 + 8);
    temp_s1->f4 = arg2;
    temp_s1->f8 = arg3;
    temp_s1->f12 = 0;
    temp_s1->f16 = arg5;
    temp_s1->f20 = arg4;
    temp_s1->f24 = arg6;
    temp_s1->f28 = arg7;
    FUN_0010b7d8(arg2, arg2 + arg3);
    temp_a0 = arg0->f8;
    FUN_0010b7d8(temp_a0, temp_a0 + 0x80);
    FUN_0032d6d0(&sp4C, arg0->f12, 6, temp_s1, 0x20, p, 0x10, 1);
    return *p;
}
