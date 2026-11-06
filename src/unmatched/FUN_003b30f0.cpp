extern "C" {
void *beNDMWShopTitle03_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003b30f0(void);
}
void FUN_003b30f0(void)
{
    igMetaObject_RunStaticInit(beNDMWShopTitle03_Register);
}
