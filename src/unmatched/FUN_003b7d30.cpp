extern "C" {
void *beNDMWShopCtrlA1_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003b7d30(void);
}
void FUN_003b7d30(void)
{
    igMetaObject_RunStaticInit(beNDMWShopCtrlA1_Register);
}
