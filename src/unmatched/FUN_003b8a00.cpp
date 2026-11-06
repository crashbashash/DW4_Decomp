extern "C" {
void *beNDMWShopCtrlEvolve_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003b8a00(void);
}
void FUN_003b8a00(void)
{
    igMetaObject_RunStaticInit(beNDMWShopCtrlEvolve_Register);
}
