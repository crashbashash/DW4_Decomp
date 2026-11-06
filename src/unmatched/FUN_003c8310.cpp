extern "C" {
void *beNDMWItemImportant_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003c8310(void);
}
void FUN_003c8310(void)
{
    igMetaObject_RunStaticInit(beNDMWItemImportant_Register);
}
