extern "C" {
void *beNDMWItemRevisionPocketBase_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003c8e60(void);
}
void FUN_003c8e60(void)
{
    igMetaObject_RunStaticInit(beNDMWItemRevisionPocketBase_Register);
}
