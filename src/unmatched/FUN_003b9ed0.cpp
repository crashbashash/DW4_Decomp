extern "C" {
void *beNDMWStatusCtrlFlag_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003b9ed0(void);
}
void FUN_003b9ed0(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusCtrlFlag_Register);
}
