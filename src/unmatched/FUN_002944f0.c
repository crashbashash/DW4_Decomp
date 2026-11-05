/* Looks up a value through FUN_002b2d20 (query id 224) and maps result 1/3/6 to 33/81/97; every other result, or a failed lookup, gives 17. */
extern int FUN_002b2d20(void *, int, int *);
int FUN_002944f0(void *h)
{
    int v;
    int ret;
    if (!FUN_002b2d20(h, 224, &v))
        return 17;
    switch (v) {
    case 1: ret = 33; break;
    case 3: ret = 81; break;
    case 6: ret = 97; break;
    case 0: case 2: case 4: case 5: case 7: case 8:
    default: ret = 17; break;
    }
    return ret;
}
