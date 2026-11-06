typedef struct S0 { char pad1372[1372]; unsigned char f55C; } S0;
int FUN_001e74b0();
int FUN_001e7500();
extern int DAT_00560920[4];
void FUN_00174300(S0 *arg0, unsigned char arg1) {
    int temp_v1;

    temp_v1 = arg1 & 0xFF;
    if (arg0->f55C == temp_v1) {
        DAT_00560920[0] += 1;
    }
    arg0->f55C = arg1;
    if (temp_v1 == 1) {
        FUN_001e74b0(0x12);
        return;
    }
    FUN_001e7500(0x12);
}
