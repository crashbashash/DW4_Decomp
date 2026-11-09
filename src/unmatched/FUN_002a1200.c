typedef struct FrmScanObj {
    char pad[40];
    int limit;
} FrmScanObj;

int FUN_002a12f8(FrmScanObj *obj, int *a, int *b, int limit, int *c);
int FUN_002a1360(FrmScanObj *obj, int n);
int FUN_002a1380(FrmScanObj *obj, int a, int b, int *n, int *m, int c);
void FUN_002a2a90(FrmScanObj *obj, int total, int frames);

int FUN_002a1200(FrmScanObj *obj)
{
    int ret = 0;
    int total = 0;
    int frames = 0;
    int limit = obj->limit;
    int a, b, c;
    int n, m;

    while (total < 0x7FFFFFFF) {
        ret = FUN_002a12f8(obj, &a, &b, limit, &c);
        if (ret != 0)
            break;
        ret = FUN_002a1380(obj, a, b, &n, &m, c);
        if (ret != 0 || n == 0)
            break;
        ret = FUN_002a1360(obj, n);
        if (ret != 0)
            break;
        frames += m;
        total += n;
    }
    FUN_002a2a90(obj, total, frames);
    return ret;
}
