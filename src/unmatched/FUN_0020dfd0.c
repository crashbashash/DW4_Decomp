int FUN_0020d270();
int WaitSema();
extern int DAT_00568ed0[4];
extern int DAT_0056c174[4];
extern volatile int DAT_0056c640[4];
extern int DAT_0056c648[4];
void FUN_0020dfd0(int arg0) {
    /* matching construct: variant search — decl order [1, 0]; the unit compiler (combat build -O3,p -Iinclude) assigns stack slots and registers in declaration order, the reverse of the 2001 default */
    long long sp28;
    long long sp20;

    FUN_0020d270(&sp28);
    DAT_00568ed0[0] = DAT_0056c640[0];
    WaitSema(DAT_0056c640[0]);
    DAT_00568ed0[0] = -1;
    FUN_0020d270(&sp20);
    DAT_0056c648[0] = arg0;
    DAT_0056c174[0] += (long long) ((sp20 - sp28) << 0x20) >> 0x20;
}
