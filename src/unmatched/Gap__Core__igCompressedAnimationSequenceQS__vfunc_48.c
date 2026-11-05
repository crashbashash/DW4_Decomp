int FUN_00192ab0(int *, int *, int *, float);
int FUN_00192cc0(int *, int *, int *, float);
int FUN_001bf560(void *, void *, void *);
struct S { char pad[58]; unsigned char f58; };
void Gap__Core__igCompressedAnimationSequenceQS__vfunc_48(struct S *arg0, int *arg1, void *arg2, int *arg3, float fparg0) {
    int sp80[4]; int sp70[4]; int sp60[4]; int sp50[4];
    unsigned char t;
    t = arg0->f58;
    if (t == 0) {
        FUN_001bf560(arg0, arg2, arg1);
        return;
    }
    if (t == 3) {
        FUN_001bf560(arg0, arg2, sp80);
        FUN_001bf560(arg0, arg3, sp70);
        FUN_00192ab0(arg1, sp80, sp70, fparg0);
        return;
    }
    FUN_001bf560(arg0, arg2, sp60);
    FUN_001bf560(arg0, arg3, sp50);
    FUN_00192cc0(arg1, sp60, sp50, fparg0);
}
