typedef struct HdrSkipObj {
    char pad[40];
    int hdrlen;
} HdrSkipObj;

int MPS_GetStartCodeKind(unsigned char * p);
int FUN_002a1730(unsigned char *p, int n);
int FUN_002a1770(HdrSkipObj *obj, unsigned char *p);

void FUN_002a1650(HdrSkipObj *obj, unsigned char *buf, int size, int *skip)
{
    int n;
    int count;

    *skip = 0;
    n = obj->hdrlen;
    if (size >= n + 3 && FUN_002a1730(buf, n) != 0) {
        *skip = n;
        return;
    }
    count = 0;
    while (size >= 4) {
        if (MPS_GetStartCodeKind(buf++) & 0xD0000) {
            *skip = count;
            return;
        }
        size--;
        count++;
    }
    if (size >= 1 && size <= 3 && FUN_002a1770(obj, buf + size) != 0)
        count += size;
    *skip = count;
}
