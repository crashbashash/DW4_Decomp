extern "C" {
void *beNDMWLoadSlotPlayer_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003c6520(void);
}
void FUN_003c6520(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadSlotPlayer_Register);
}
