extern "C" {
void *beNDMWShopCtrlSales_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003b6cf0(void);
}
void FUN_003b6cf0(void)
{
    igMetaObject_RunStaticInit(beNDMWShopCtrlSales_Register);
}
