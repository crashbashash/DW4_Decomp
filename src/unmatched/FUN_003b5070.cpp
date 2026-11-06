extern "C" {
void *beNDMWShopSelect00_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003b5070(void);
}
void FUN_003b5070(void)
{
    igMetaObject_RunStaticInit(beNDMWShopSelect00_Register);
}
