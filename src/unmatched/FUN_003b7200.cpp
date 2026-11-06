extern "C" {
void *beNDMWShopCtrlDeviceSell_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003b7200(void);
}
void FUN_003b7200(void)
{
    igMetaObject_RunStaticInit(beNDMWShopCtrlDeviceSell_Register);
}
