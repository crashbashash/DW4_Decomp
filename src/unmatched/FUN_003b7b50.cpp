extern "C" {
void *beNDMWShopCtrlA2_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003b7b50(void);
}
void FUN_003b7b50(void)
{
    igMetaObject_RunStaticInit(beNDMWShopCtrlA2_Register);
}
