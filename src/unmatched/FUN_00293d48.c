extern char DAT_004f3178[];
int FUN_00294d28(void);
int FUN_00298b18(int obj);
int FUN_0029a320(char *msg);

typedef struct FrmTypeInfo {
    char pad[88];
    unsigned int state;
    char pad92[16];
    signed char flag;
} FrmTypeInfo;

int FUN_00293d48(int obj, FrmTypeInfo *info)
{
    int ret = 0;

    switch (info->state) {
    case 1:
    case 2:
        ret = 2;
        break;
    case 3:
        if (info->flag == 0)
            ret = 2;
        break;
    case 0:
    default:
        FUN_0029a320(DAT_004f3178);
        break;
    }
    if (FUN_00294d28() == 1 && FUN_00298b18(obj) == 1)
        ret = 2;
    return ret;
}
