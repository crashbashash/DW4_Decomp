extern "C" {
void *beNDMWStatusCtrlEquip_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003badf0(void);
}
void FUN_003badf0(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusCtrlEquip_Register);
}
