int FUN_0027b2e0();
int memset();
extern char DAT_004f1a78[];
extern char DAT_004f1aa8[];

typedef struct {
    int f0;
    int f4;
} CriWork;

void FUN_0027b548(CriWork *work)
{
    if (work == 0) {
        FUN_0027b2e0(DAT_004f1a78);
        return;
    }
    if (work->f4 == 0) {
        FUN_0027b2e0(DAT_004f1aa8);
        return;
    }
    memset(work, 0, 36);
    work->f4 = 0;
}
