extern "C" {
void *beNDMWShopCtrlA0_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003b8060(void);
}
void FUN_003b8060(void)
{
    igMetaObject_RunStaticInit(beNDMWShopCtrlA0_Register);
}
