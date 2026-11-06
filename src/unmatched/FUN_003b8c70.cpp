extern "C" {
void *beNDMWShopCtrl10_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003b8c70(void);
}
void FUN_003b8c70(void)
{
    igMetaObject_RunStaticInit(beNDMWShopCtrl10_Register);
}
