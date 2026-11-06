extern "C" {
void *beNDMWLoadIntf2SelSlot_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003c2f80(void);
}
void FUN_003c2f80(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadIntf2SelSlot_Register);
}
