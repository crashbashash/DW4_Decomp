int SJERR_CallErr();
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
        SJERR_CallErr(DAT_004f1d98);
        return;
    }
    if (work->f4 == 0) {
        SJERR_CallErr(DAT_004f1dc8);
        return;
    }
    memset(work, 0, 64);
    work->f4 = 0;
}
