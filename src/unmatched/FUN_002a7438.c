typedef struct SjScanArea {
    signed char *addr0;
    int len0;
    signed char *addr1;
    int len1;
    int f16[4];
} SjScanArea;

typedef struct SjScanObj {
    char pad[2464];
    long long total;
    long long payload;
    char pad2480[5648];
    int sj;
} SjScanObj;

int FUN_0029dd98(SjScanObj *obj, int sj, SjScanArea *area);
signed char *FUN_002a41a8(SjScanArea *area, int mask, int *code);
void FUN_002a7598(SjScanObj *obj, int n);

int FUN_002a7438(SjScanObj *obj, int unused, int mask)
{
    SjScanArea area;
    int code;
    signed char *p;
    int n;
    int i;
    int found;
    int c;

    if (FUN_0029dd98(obj, obj->sj, &area) != 0)
        return 0;
    if (area.len0 == 0)
        return 0;
    p = FUN_002a41a8(&area, mask, &code);
    if (p == 0) {
        n = area.len0 + area.len1 - 3;
        if (n < 0)
            n = 0;
    } else if (p >= area.addr0 && p < area.addr0 + area.len0)
        n = p - area.addr0;
    else if (p >= area.addr1 && p < area.addr1 + area.len1)
        n = p - area.addr1 + area.len0;
    else
        n = 0;
    FUN_002a7598(obj, n);
    found = 0;
    for (i = 0; i < (n < 4 ? n : 3); i++) {
        if (i < area.len0)
            c = area.addr0[i];
        else
            c = area.addr1[i - area.len0];
        if (c != 0) {
            found = 1;
            break;
        }
    }
    if (found)
        obj->payload += n;
    obj->total += n;
    return n;
}
