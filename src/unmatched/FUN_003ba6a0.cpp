extern "C" {
void *beNDMWStatusSubSlot_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003ba6a0(void);
}
void FUN_003ba6a0(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusSubSlot_Register);
}
