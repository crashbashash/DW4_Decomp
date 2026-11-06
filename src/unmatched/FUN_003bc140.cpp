extern "C" {
void *beNDMWSaveIntfInfo_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003bc140(void);
}
void FUN_003bc140(void)
{
    igMetaObject_RunStaticInit(beNDMWSaveIntfInfo_Register);
}
