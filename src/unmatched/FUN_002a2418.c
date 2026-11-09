int FUN_0029ed48(void *h);
int FUN_0029ed68(void *h);

int FUN_002a2418(void *h, int type)
{
    if (type != 0x80000)
        return 0;
    if (FUN_0029ed48(h) || FUN_0029ed68(h))
        return 0;
    return 1;
}
