extern "C" {
void *beNDMWItemRevisionBase_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003c8fd0(void);
}
void FUN_003c8fd0(void)
{
    igMetaObject_RunStaticInit(beNDMWItemRevisionBase_Register);
}
