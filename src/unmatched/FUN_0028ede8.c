typedef struct InfoCopyInfo {
    int w[32];
} InfoCopyInfo;

typedef struct InfoCopyObj {
    char pad[464];
    InfoCopyInfo info;
} InfoCopyObj;

int FUN_0028eb38(int obj, int code);
int FUN_002913f8(InfoCopyObj *obj);

int FUN_0028ede8(InfoCopyObj *obj, InfoCopyInfo *info)
{
    if (FUN_002913f8(obj) != 0)
        return FUN_0028eb38(0, 0xFF03020C);
    *info = obj->info;
    return 0;
}
