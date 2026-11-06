extern "C" {
void *beSvSlotPS2_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0034a6c0(void);
}
void FUN_0034a6c0(void)
{
    igMetaObject_RunStaticInit(beSvSlotPS2_Register);
}
