extern "C" {
void *beNDMWStatusCtrlBaseEquip_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003baaf0(void);
}
void FUN_003baaf0(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusCtrlBaseEquip_Register);
}
