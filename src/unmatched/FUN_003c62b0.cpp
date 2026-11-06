extern "C" {
void *beNDMWLoadSlotPlayerList_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003c62b0(void);
}
void FUN_003c62b0(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadSlotPlayerList_Register);
}
