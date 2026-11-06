extern "C" {
void *beNDMWItemDisk_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003c86d0(void);
}
void FUN_003c86d0(void)
{
    igMetaObject_RunStaticInit(beNDMWItemDisk_Register);
}
