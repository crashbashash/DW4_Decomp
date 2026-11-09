int FUN_0029fee0(int obj, int a, int b, int c, int *split);
int FUN_002a2e28(int obj);
int FUN_002a1e50(int obj, int a, int b, int c);

int FUN_002a1db0(int obj, int a, int b, int c)
{
    int split;

    if (FUN_0029fee0(obj, a, b, c, &split) != 0) {
        FUN_002a2e28(obj);
        if (split != 0)
            FUN_002a1e50(obj, 0, b - 18, c + 18);
        return 1;
    }
    return FUN_002a1e50(obj, a, b, c);
}
