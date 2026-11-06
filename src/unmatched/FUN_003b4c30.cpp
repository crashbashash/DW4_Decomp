extern "C" {
void *beNDMWShopSelect02_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003b4c30(void);
}
void FUN_003b4c30(void)
{
    igMetaObject_RunStaticInit(beNDMWShopSelect02_Register);
}
