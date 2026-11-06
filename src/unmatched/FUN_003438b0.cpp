extern "C" {
void *beStaticInfoCtl_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003438b0(void);
}
void FUN_003438b0(void)
{
    igMetaObject_RunStaticInit(beStaticInfoCtl_Register);
}
