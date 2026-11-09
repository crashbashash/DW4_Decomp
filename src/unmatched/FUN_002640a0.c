extern volatile long long DAT_0049da78;
extern volatile long long DAT_0049da80;
extern volatile long long DAT_0049da00;
extern volatile int DAT_0049d9d4;
extern volatile int DAT_0049d9c4;
extern volatile int DAT_0049da30;
extern volatile int DAT_0049daa8;
int FUN_0027eb10(void);
void FUN_00264350(void);
int FUN_00264808(void);
int FUN_00264368(int sema);
void FUN_00264300(int sema);
void FUN_00265838(void);
void ExitDeleteThread(void);

void FUN_002640a0(void)
{
    int busy;

    while (DAT_0049da78 == 0) {
        DAT_0049da00++;
        DAT_0049d9d4 = 1;
        busy = FUN_0027eb10();
        DAT_0049d9d4 = 0;
        if (DAT_0049d9c4 == 1) {
            DAT_0049d9c4 = 0;
            FUN_00264350();
        }
        if (busy == 0) {
            if (FUN_00264808() == 1) {
                if (FUN_00264368(DAT_0049da30) == DAT_0049da30) {
                    FUN_00264300(DAT_0049da30);
                }
            }
            if (DAT_0049d9c4 != 1) {
                FUN_00265838();
                DAT_0049daa8 = 1;
            }
            FUN_00264350();
        }
    }
    DAT_0049da80 = 1;
    ExitDeleteThread();
}
