extern "C" {
void *beNDMWStatusMainSlot_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003ba850(void);
}
void FUN_003ba850(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusMainSlot_Register);
}
