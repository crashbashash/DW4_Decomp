extern "C" {
void *beSelectCtrlInfoWork_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00345830(void);
}
void FUN_00345830(void)
{
    igMetaObject_RunStaticInit(beSelectCtrlInfoWork_Register);
}
