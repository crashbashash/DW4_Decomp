extern "C" {
void *beNDMWSaveCtrl_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003bd540(void);
}
void FUN_003bd540(void)
{
    igMetaObject_RunStaticInit(beNDMWSaveCtrl_Register);
}
