typedef struct SubCreateSub {
    int pos;
} SubCreateSub;

typedef struct SubCreateInfo {
    int f0;
    int f4;
    SubCreateSub sub;
    char pad12[28];
    int unit;
} SubCreateInfo;

void FUN_0029d5f8(void *tmp, SubCreateSub *sub, int a);
int FUN_0029d638(int obj, void *tmp, SubCreateSub *sub, int kind, int arg);
void FUN_0029d838(int ctx, int obj, void *tmp, SubCreateSub *sub, int kind);
void FUN_0029d8f0(int obj, void *tmp, SubCreateSub *sub, int kind);
void FUN_0029da18(int obj, void *tmp, SubCreateSub *sub, int kind);

int FUN_0029d4c0(int ctx, int obj, SubCreateInfo *info)
{
    SubCreateSub *sub = &info->sub;
    int tmp[8];
    int ret;

    FUN_0029d5f8(tmp, sub, info->f4);
    ret = FUN_0029d638(obj, tmp, sub, 0, sub->pos % info->unit);
    if (ret != 0)
        return ret;
    ret = FUN_0029d638(obj, tmp, sub, 1, 2048);
    if (ret != 0)
        return ret;
    ret = FUN_0029d638(obj, tmp, sub, 2, 0);
    if (ret != 0)
        return ret;
    FUN_0029d838(ctx, obj, tmp, sub, 3);
    FUN_0029d8f0(obj, tmp, sub, 4);
    FUN_0029d838(ctx, obj, tmp, sub, 5);
    FUN_0029d8f0(obj, tmp, sub, 6);
    FUN_0029da18(obj, tmp, sub, 7);
    return 0;
}
