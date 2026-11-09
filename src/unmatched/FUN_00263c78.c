extern int DAT_0049d990;
extern volatile int DAT_0049d9c4;
extern char DAT_004ee2d0[];
int ChangeThreadPriority(int thid, int prio);
void FUN_00264300(int thid);
void FUN_00264368(int thid);
void FUN_0027e398(const char *message);

void FUN_00263c78(int thid, int prio)
{
    int i;

    if (thid == 0) {
        return;
    }
    DAT_0049d9c4 = 1;
    ChangeThreadPriority(thid, DAT_0049d990);
    for (i = 0; ; i++) {
        FUN_00264300(thid);
        FUN_00264368(thid);
        if (DAT_0049d9c4 == 0) {
            break;
        }
        if (i > 0x0BEBC1FF) {
            FUN_0027e398(DAT_004ee2d0);
            break;
        }
    }
    ChangeThreadPriority(thid, prio);
}
