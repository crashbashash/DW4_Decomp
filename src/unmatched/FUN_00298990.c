int FUN_002968c0(void *ply);
int FUN_00297810(void *ply);
void FUN_00297838(void *ply, int *src, int *work);
void FUN_002b3690(int handle, int *work);
void FUN_0029a320(const char *message);

extern char DAT_004f4468[];
extern char DAT_004f4498[];

void FUN_00298990(void *ply, int *src)
{
    int work[36];
    int handle;

    if (FUN_002968c0(ply) == 0) {
        FUN_0029a320(DAT_004f4468);
        return;
    }
    if (*src == 0) {
        FUN_0029a320(DAT_004f4498);
        return;
    }
    handle = FUN_00297810(ply);
    FUN_00297838(ply, src, work);
    FUN_002b3690(handle, work);
}
