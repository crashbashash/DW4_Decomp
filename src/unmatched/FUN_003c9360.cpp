extern "C" {
void *beNDMWItemBase_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003c9360(void);
}
void FUN_003c9360(void)
{
    igMetaObject_RunStaticInit(beNDMWItemBase_Register);
}
