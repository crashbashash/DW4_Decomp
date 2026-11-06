extern "C" {
struct R { char pad[4]; int f4; char pad2[12]; char f20; };
struct S { char pad[8]; struct R *f8; };
int FUN_00236ab0(int, struct R *);
struct R *FUN_00336bd0(int);
int Memory_GetAllocatorBySelector(int);
int igObject_Destroy(struct R *);
int igObject_GetAllocator(struct S *);
extern int DAT_00587108[4];
extern unsigned char GPR_00554c14;
void Gap__igMoviePlugin__vfunc_21(struct S *arg0, int arg1) {
    int var_v0;
    struct R *temp_a0;
    var_v0 = igObject_GetAllocator(arg0);
    var_v0 = GPR_00554c14 != 0 ? var_v0 : Memory_GetAllocatorBySelector(DAT_00587108[0]);
    temp_a0 = arg0->f8;
    if (temp_a0 != 0) {
        temp_a0->f4 = temp_a0->f4 - 1;
        if ((temp_a0->f4 & 0x7FFFFF) == 0) {
            igObject_Destroy(temp_a0);
        }
    }
    arg0->f8 = FUN_00336bd0(var_v0);
    arg0->f8->f20 = 1;
    FUN_00236ab0(arg1, arg0->f8);
}
}
