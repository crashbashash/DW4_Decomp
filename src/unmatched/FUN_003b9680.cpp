extern "C" {
void *beNDMWStatusCtrlSendBit_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003b9680(void);
}
void FUN_003b9680(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusCtrlSendBit_Register);
}
