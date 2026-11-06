extern "C" {
void *beSelectCtrl_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00345bc0(void);
}
void FUN_00345bc0(void)
{
    igMetaObject_RunStaticInit(beSelectCtrl_Register);
}
