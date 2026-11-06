extern "C" {
void *beNDMWStatusCtrlD0_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003bb040(void);
}
void FUN_003bb040(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusCtrlD0_Register);
}
