extern "C" {
void *beNDMWShopDevice_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003b67e0(void);
}
void FUN_003b67e0(void)
{
    igMetaObject_RunStaticInit(beNDMWShopDevice_Register);
}
