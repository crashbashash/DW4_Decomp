extern "C" {
void *beMatCtrl_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0035a880(void);
}
void FUN_0035a880(void)
{
    igMetaObject_RunStaticInit(beMatCtrl_Register);
}
