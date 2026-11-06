extern "C" {
void *beNDMWShopTitle01_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003b32c0(void);
}
void FUN_003b32c0(void)
{
    igMetaObject_RunStaticInit(beNDMWShopTitle01_Register);
}
