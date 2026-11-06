extern "C" {
void *beDemoKeepMes_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00363d60(void);
}
void FUN_00363d60(void)
{
    igMetaObject_RunStaticInit(beDemoKeepMes_Register);
}
