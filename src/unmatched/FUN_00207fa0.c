int FUN_00113f20();
int FUN_00113f78();
int FUN_00208120();
int FUN_0020d270(long long *);
int WaitSema(int);
extern int DAT_00568ed0[4];
extern volatile int DAT_0056bf80[4];
extern unsigned int DAT_0056bfc0[4];
extern int DAT_0056bfd8[4];
extern int DAT_0056c164[4];
extern volatile int DAT_0056d670[4];
extern volatile int DAT_0056d678[4];
void FUN_00207fa0(unsigned int arg0) {
    long long sp20;
    long long sp28;
    FUN_00208120();
    FUN_00113f20();
    DAT_0056d670[0] |= 8;
    FUN_00113f78();
    goto test;
body:
    FUN_0020d270(&sp28);
    DAT_00568ed0[0] = DAT_0056bf80[0];
    WaitSema(DAT_0056bf80[0]);
    DAT_00568ed0[0] = -1;
    FUN_0020d270(&sp20);
    DAT_0056c164[0] += (long long)((sp20 - sp28) << 0x20) >> 0x20;
test:
    if (DAT_0056bfc0[0] < arg0) goto body;
    FUN_00113f20();
    DAT_0056d670[0] &= ~8;
    DAT_0056d678[0] &= ~8;
    FUN_00113f78();
    DAT_0056bfd8[0] -= 1;
}
