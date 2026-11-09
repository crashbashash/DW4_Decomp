extern volatile long long DAT_0049da68;
extern volatile long long DAT_0049da70;
extern volatile long long DAT_0049d9f8;
extern volatile int DAT_0049d9d0;
extern unsigned short DAT_0049daa4;
int FUN_0027eae0(void);
void FUN_00264350(void);
void ExitDeleteThread(void);

void FUN_00263fc0(void)
{
    while (DAT_0049da68 == 0) {
        DAT_0049d9f8++;
        DAT_0049d9d0 = 1;
        if (DAT_0049daa4 != 0) {
            *(volatile unsigned long long *)0x120000E0 = DAT_0049daa4;
        }
        FUN_0027eae0();
        if (DAT_0049daa4 != 0) {
            *(volatile unsigned long long *)0x120000E0 = 0;
        }
        DAT_0049d9d0 = 0;
        FUN_00264350();
    }
    DAT_0049da70 = 1;
    ExitDeleteThread();
}
