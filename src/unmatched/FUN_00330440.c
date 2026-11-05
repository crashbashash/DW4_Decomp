int FUN_003304e0();
extern int DAT_005871d0[4];
struct S330440 { char pad[52]; int f; };
void FUN_00330440(struct S330440 *arg0, int arg1) {
    arg0->f = arg1;
    FUN_003304e0(DAT_005871d0[0], arg0);
}
