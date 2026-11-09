int FUN_0027b2e0();
int memset();
extern char DAT_004f2048[];
extern char DAT_004f2078[];

typedef struct {
    int f0;
    signed char f4;
} CriWork;

void FUN_0027c9f8(CriWork *work)
{
    if (work == 0) {
        FUN_0027b2e0(DAT_004f2048);
        return;
    }
    if (work->f4 == 0) {
        FUN_0027b2e0(DAT_004f2078);
        return;
    }
    memset(work, 0, 48);
    work->f4 = 0;
}
