extern "C" {
void *beNDMWShopCtrl30_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003b8740(void);
}
void FUN_003b8740(void)
{
    igMetaObject_RunStaticInit(beNDMWShopCtrl30_Register);
}
