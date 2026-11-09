int FUN_0027b2e0();
int memset();
extern char DAT_004f1d98[];
extern char DAT_004f1dc8[];

typedef struct {
    int f0;
    int f4;
} CriWork;

void FUN_0027bea0(CriWork *work)
{
    if (work == 0) {
        FUN_0027b2e0(DAT_004f1d98);
        return;
    }
    if (work->f4 == 0) {
        FUN_0027b2e0(DAT_004f1dc8);
        return;
    }
    memset(work, 0, 64);
    work->f4 = 0;
}
