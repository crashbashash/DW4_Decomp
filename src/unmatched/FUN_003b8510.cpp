extern "C" {
void *beNDMWShopCtrl40_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003b8510(void);
}
void FUN_003b8510(void)
{
    igMetaObject_RunStaticInit(beNDMWShopCtrl40_Register);
}
