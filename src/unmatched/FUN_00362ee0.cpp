extern "C" {
void *beFile_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00362ee0(void);
}
void FUN_00362ee0(void)
{
    igMetaObject_RunStaticInit(beFile_Register);
}
