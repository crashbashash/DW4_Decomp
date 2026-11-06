extern "C" {
void *beNDMWShopSelect01_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003b4ea0(void);
}
void FUN_003b4ea0(void)
{
    igMetaObject_RunStaticInit(beNDMWShopSelect01_Register);
}
