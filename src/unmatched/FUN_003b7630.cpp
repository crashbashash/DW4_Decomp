extern "C" {
void *beNDMWShopCtrlEditBit_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003b7630(void);
}
void FUN_003b7630(void)
{
    igMetaObject_RunStaticInit(beNDMWShopCtrlEditBit_Register);
}
