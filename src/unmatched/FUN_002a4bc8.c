int FUN_002a0bb8();

int FUN_002a4bc8(int obj, int status, int n, int code)
{
    switch (status) {
    case 0:
        return 0;
    case -2:
        if (n > 0)
            return 0;
        return FUN_002a0bb8(obj, status);
    case -3:
        if (n > 0)
            return 0;
        return FUN_002a0bb8(obj, status);
    default:
        return FUN_002a0bb8(obj, code);
    }
}
