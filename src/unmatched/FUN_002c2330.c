void *igLibraryLoader_Register(void);
void FUN_002c2330(void)
{
    igMetaObject_RunStaticInit(igLibraryLoader_Register);
}
