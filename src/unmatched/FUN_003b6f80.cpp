extern "C" {
void *beNDMWShopCtrlDiskSell_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003b6f80(void);
}
void FUN_003b6f80(void)
{
    igMetaObject_RunStaticInit(beNDMWShopCtrlDiskSell_Register);
}
