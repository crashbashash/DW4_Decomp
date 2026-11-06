extern "C" {
void *beNDMWShopTitle00_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003b3480(void);
}
void FUN_003b3480(void)
{
    igMetaObject_RunStaticInit(beNDMWShopTitle00_Register);
}
