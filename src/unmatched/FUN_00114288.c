void GetOsdConfigParam(void *param);
int SetOsdConfigParam(void *param);

int FUN_00114288(void)
{
    unsigned int saved;
    unsigned int probe;
    GetOsdConfigParam(&saved);
    probe = (saved & 0xFFFF1FFF) | 0x2000;
    SetOsdConfigParam(&probe);
    GetOsdConfigParam(&probe);
    SetOsdConfigParam(&saved);
    return ((probe >> 13) & 7) == 0;
}
