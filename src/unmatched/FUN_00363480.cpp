extern "C" {
void *beDemoManager_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00363480(void);
}
void FUN_00363480(void)
{
    igMetaObject_RunStaticInit(beDemoManager_Register);
}
