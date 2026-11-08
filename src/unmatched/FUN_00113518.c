unsigned int sceSifGetReg(unsigned int reg);
void FUN_0010b360(void);
void FUN_00116090(int a, int b);

int FUN_00113518(void)
{
    if (!(sceSifGetReg(4) & 0x40000)) {
        return 0;
    }
    FUN_0010b360();
    FUN_00116090(1, 1);
    FUN_00116090(0, 1);
    return 1;
}
