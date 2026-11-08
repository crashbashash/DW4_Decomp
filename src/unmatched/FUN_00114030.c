int *FUN_00114030(int *p, int *end, int value)
{
    while (*p != value && p < end) {
        p++;
    }
    return p < end ? p : 0;
}
