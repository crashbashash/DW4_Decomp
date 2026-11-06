int FUN_00113f20();
int FUN_00113f78();
long long FUN_001f03a0();
int FUN_00204240();
struct N { int f0; struct N *f4; long long f8; int f16; int f20; };
extern struct N *DAT_0056bf40[4];
extern struct N *DAT_0056bf48[4];
extern struct N *DAT_0056bf50[4];
void FUN_00207e70(int arg0, int arg1) {
    struct N *temp_s0;

    if (DAT_0056bf50[0] == 0) {
        FUN_00204240(9, &DAT_0056bf50[0]);
    }
    FUN_00113f20();
    temp_s0 = DAT_0056bf50[0];
    DAT_0056bf50[0] = temp_s0->f4;
    FUN_00113f78();
    temp_s0->f8 = FUN_001f03a0();
    temp_s0->f16 = arg0;
    temp_s0->f20 = arg1;
    temp_s0->f4 = 0;
    FUN_00113f20();
    if (DAT_0056bf40[0] != 0) {
        DAT_0056bf40[0]->f4 = temp_s0;
    } else {
        DAT_0056bf48[0] = temp_s0;
    }
    DAT_0056bf40[0] = temp_s0;
    FUN_00113f78();
}
