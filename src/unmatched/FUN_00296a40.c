typedef struct SetSyncPly {
    char pad[12];
    int f12;
    char pad16[48];
    int handle;
} SetSyncPly;

extern char DAT_004f3c60[];
int FUN_002968c0(SetSyncPly *ply);
void FUN_0029a320(const char *format, ...);
void FUN_002ad950(int handle, int id, int value);

void FUN_00296a40(SetSyncPly *ply, int mode)
{
    int handle;

    if (FUN_002968c0(ply) == 0) {
        FUN_0029a320(DAT_004f3c60);
        return;
    }
    handle = ply->handle;
    if (mode == 0) {
        FUN_002ad950(handle, 15, 0);
        return;
    }
    if (mode == 1) {
        FUN_002ad950(handle, 15, 1);
        return;
    }
    if (mode == 2) {
        if (ply->f12 == 1) {
            FUN_002ad950(handle, 15, 2);
            return;
        }
        FUN_002ad950(handle, 15, 1);
        return;
    }
    if (mode != 3)
        return;
    FUN_002ad950(handle, 15, 5);
    FUN_002ad950(handle, 71, 1);
}
