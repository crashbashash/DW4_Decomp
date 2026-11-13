extern char DAT_004f3c90[];
extern char DAT_004f3cc0[];
int FUN_002968c0(void *obj);
void mwsfd_Error(char *msg);
int FUN_002adba0(int handle, int id, int *value);

typedef struct SyncModeObj {
    char pad[64];
    int handle;
} SyncModeObj;

int FUN_00296b98(SyncModeObj *obj)
{
    int value;
    int ret;

    if (FUN_002968c0(obj) == 0) {
        mwsfd_Error(DAT_004f3c90);
        return -1;
    }
    FUN_002adba0(obj->handle, 15, &value);
    switch (value) {
    case 0:
        ret = 0;
        break;
    case 1:
        ret = 1;
        break;
    case 2:
        ret = 2;
        break;
    default:
        mwsfd_Error(DAT_004f3cc0);
        ret = -1;
        break;
    }
    return ret;
}
