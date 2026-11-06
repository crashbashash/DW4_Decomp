extern "C" {
void *beNDMWShopSelect03_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003b4a60(void);
}
void FUN_003b4a60(void)
{
    igMetaObject_RunStaticInit(beNDMWShopSelect03_Register);
}
