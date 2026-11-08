void FUN_00113fe8(void *dst, void *src, int size);
extern int *D_00482578;

int FUN_00114080(int index)
{
    int value;
    FUN_00113fe8(&value, D_00482578 + index, 4);
    return value;
}
