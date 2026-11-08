unsigned int sceSifGetReg(unsigned int reg);
void FUN_0010b360(void);
void sceSifExecNotifyHandler(int a, int b);

int sceSifSyncIop(void)
{
    if (!(sceSifGetReg(4) & 0x40000)) {
        return 0;
    }
    FUN_0010b360();
    sceSifExecNotifyHandler(1, 1);
    sceSifExecNotifyHandler(0, 1);
    return 1;
}
