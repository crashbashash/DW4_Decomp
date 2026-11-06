extern "C" {
void *beNDMWShinkaCtrl_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003c9650(void);
}
void FUN_003c9650(void)
{
    igMetaObject_RunStaticInit(beNDMWShinkaCtrl_Register);
}
