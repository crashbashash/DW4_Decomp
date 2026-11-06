extern "C" {
void *beSaveIntfComMdlData_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003bc820(void);
}
void FUN_003bc820(void)
{
    igMetaObject_RunStaticInit(beSaveIntfComMdlData_Register);
}
