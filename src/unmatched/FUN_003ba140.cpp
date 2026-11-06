extern "C" {
void *beNDMWStatusCtrlFolder_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003ba140(void);
}
void FUN_003ba140(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusCtrlFolder_Register);
}
