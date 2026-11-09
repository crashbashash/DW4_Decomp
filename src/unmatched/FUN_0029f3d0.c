char *FUN_0029f798(char *buf, int size, int code);
void FUN_0029f4b8(char *p, int size, int *out);

int FUN_0029f3d0(char *buf, int size, int *out)
{
    char *first;
    char *second;
    char *third;
    int offset;
    int rest;
    int gap;

    *out = 0;
    first = FUN_0029f798(buf, size, 0x10000);
    offset = first - buf;
    rest = size - offset;
    if (first == 0)
        return 0;
    second = FUN_0029f798(first + 1, rest - 1, 0x10000);
    if (second == 0)
        return 0;
    third = FUN_0029f798(second + 1, size - (second - buf) - 1, 0x10000);
    if (third == 0)
        return 0;
    gap = second - first;
    if (gap != third - second)
        return -1;
    if (offset % gap != 0)
        return -1;
    FUN_0029f4b8(first, rest, out);
    return gap;
}
