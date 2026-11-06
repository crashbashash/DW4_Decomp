extern "C" {
void *beNDMWShopJunk_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003b64f0(void);
}
void FUN_003b64f0(void)
{
    igMetaObject_RunStaticInit(beNDMWShopJunk_Register);
}
