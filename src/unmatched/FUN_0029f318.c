typedef struct HdrParseInfo {
    int f0;
    void *codec;
    int f8;
    int f12;
    int type;
    int f20;
    int f24;
    int duration;
} HdrParseInfo;

extern char DAT_004f4d88[];
int FUN_0029f3d0(int obj, int src, int *count);
void FUN_0029f550(int obj, int src, HdrParseInfo *info);
void FUN_0029f690(int obj, int src, HdrParseInfo *info);
void FUN_0029fd18(int obj, int src, HdrParseInfo *info);

int FUN_0029f318(int obj, int src, HdrParseInfo *info)
{
    int count;
    int type;

    type = FUN_0029f3d0(obj, src, &count);
    if (type == 0)
        return 0;
    info->type = type;
    if (type == -1)
        return 1;
    if (count > 0)
        info->duration = count * 50;
    info->codec = DAT_004f4d88;
    FUN_0029f550(obj, src, info);
    FUN_0029f690(obj, src, info);
    FUN_0029fd18(obj, src, info);
    return 1;
}
