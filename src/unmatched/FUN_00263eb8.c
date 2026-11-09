extern volatile long long DAT_0049da58;
extern volatile long long DAT_0049da60;
extern volatile long long DAT_0049d9f0;
extern volatile int DAT_0049da2c;
extern volatile int DAT_0049da30;
extern volatile int DAT_0049daa8;
extern int DAT_0049d9c8;
int FUN_002643d0(int sema);
void FUN_00265838(void);
int FUN_00264808(void);
void FUN_00265288(void);
void FUN_0027eab0(void);
void FUN_00264350(void);
void ExitDeleteThread(void);

void FUN_00263eb8(void)
{
    while (DAT_0049da58 == 0) {
        DAT_0049d9f0++;
        FUN_002643d0(DAT_0049da2c);
        if (DAT_0049daa8 == 0) {
            FUN_00265838();
        }
        DAT_0049daa8 = 0;
        if (FUN_00264808() == 1) {
            FUN_002643d0(DAT_0049da30);
        }
        FUN_00265288();
        DAT_0049d9c8 = 1;
        FUN_0027eab0();
        DAT_0049d9c8 = 0;
        FUN_00264350();
    }
    DAT_0049da60 = 1;
    ExitDeleteThread();
}
