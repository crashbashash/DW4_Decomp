extern "C" {
void *beNDMWMcUtilCtrl_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003c5380(void);
}
void FUN_003c5380(void)
{
    igMetaObject_RunStaticInit(beNDMWMcUtilCtrl_Register);
}
