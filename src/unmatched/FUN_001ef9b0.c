int AddDmacHandler();
int FUN_0010baf8();
int FUN_00204240();
extern int DAT_00490cc0[4];
extern int DAT_00568f00[4];
extern int DAT_00568f30[4];
extern int DAT_00568f60[4];
extern long long DAT_00568f90[4];
extern long long DAT_00568fe0[4];
extern long long DAT_00569040[4];
extern unsigned char DAT_005690b8[16];
extern int DAT_00569120[4];
extern int DAT_00569190[4];
int FUN_001ef4c0();
int FUN_001ef520();
int FUN_001ef6a0();

void FUN_001ef9b0(int n) {
    if (DAT_00490cc0[n] == -1) {
        DAT_00490cc0[n] = 20;
    }
    DAT_00569120[n] = -1;
    DAT_00568f00[n] = 0;
    DAT_00568f30[n] = 0;
    FUN_00204240(n, &DAT_00568f00[n]);
    DAT_00568fe0[n] = -1;
    DAT_00568f90[n] = -1;
    DAT_00569040[n] = 0;
    DAT_00568f60[n] = DAT_00568f00[n];
    DAT_005690b8[n] = 1;
    if (n == 1) {
        DAT_00569190[n] = AddDmacHandler(n, FUN_001ef520, 0);
    } else if (n == 2) {
        DAT_00569190[n] = AddDmacHandler(n, FUN_001ef6a0, 0);
    } else if (n == 0) {
        DAT_00569190[n] = AddDmacHandler(n, FUN_001ef4c0, 0);
    }
    FUN_0010baf8(n);
}
