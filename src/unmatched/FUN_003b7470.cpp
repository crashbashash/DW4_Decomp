extern "C" {
void *beNDMWShopCtrlSell_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003b7470(void);
}
void FUN_003b7470(void)
{
    igMetaObject_RunStaticInit(beNDMWShopCtrlSell_Register);
}
