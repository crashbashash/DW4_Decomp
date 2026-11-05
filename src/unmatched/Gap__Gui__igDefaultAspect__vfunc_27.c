struct S { char pad[8]; int f8; };
int FUN_004540d0();
int FUN_00454180();
extern int DAT_0058c290[4];
extern int DAT_0058c448[4];
extern int DAT_0058c450[4];
extern int DAT_0058c460[4];
extern int DAT_0058c468[4];
void Gap__Gui__igDefaultAspect__vfunc_27(void *arg0, struct S *arg1) {
    int temp_a1;

    temp_a1 = arg1->f8;
    if ((temp_a1 == DAT_0058c450[0]) || (temp_a1 == DAT_0058c460[0]) || (temp_a1 == DAT_0058c290[0]) || (temp_a1 == DAT_0058c448[0])) {
        FUN_004540d0(arg0, temp_a1);
        return;
    }
    if (temp_a1 == DAT_0058c468[0]) {
        FUN_00454180(arg0, temp_a1);
    }
}