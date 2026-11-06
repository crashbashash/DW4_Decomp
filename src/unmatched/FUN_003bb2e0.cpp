extern "C" {
void *beNDMWStatusCtrl00_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003bb2e0(void);
}
void FUN_003bb2e0(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusCtrl00_Register);
}
