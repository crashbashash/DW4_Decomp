extern "C" {
void *beNDMWStatusCtrlBit_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003b98f0(void);
}
void FUN_003b98f0(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusCtrlBit_Register);
}
