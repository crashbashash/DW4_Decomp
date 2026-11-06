extern "C" {
void *beNDMWShopCtrlXdataChip_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003b6a60(void);
}
void FUN_003b6a60(void)
{
    igMetaObject_RunStaticInit(beNDMWShopCtrlXdataChip_Register);
}
