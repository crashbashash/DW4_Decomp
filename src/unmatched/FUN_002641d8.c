extern volatile long long DAT_0049da88;
extern volatile long long DAT_0049da90;
extern volatile long long DAT_0049da08;
extern volatile int DAT_0049d9d8;
extern volatile int DAT_0049d9c4;
int FUN_0027eb28(void);
void FUN_00264350(void);
void ExitDeleteThread(void);

void FUN_002641d8(void)
{
    int busy;

    while (DAT_0049da88 == 0) {
        DAT_0049da08++;
        DAT_0049d9d8 = 1;
        busy = FUN_0027eb28();
        DAT_0049d9d8 = 0;
        if (DAT_0049d9c4 == 1) {
            DAT_0049d9c4 = 0;
            FUN_00264350();
        }
        if (busy == 0) {
            FUN_00264350();
        }
    }
    DAT_0049da90 = 1;
    ExitDeleteThread();
}
